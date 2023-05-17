//############################################################################
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   2023 VLSI DSP course
//   HW5          : QR Cordic
//   Author         : Shun- Linag Yeh (jackyyeh1999@gmail.com)
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//   File Name   : PATTERN.v
//   Module Name : PATTERN
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//############################################################################

`define CYCLE_TIME 10.0

`define A_GOLDEN  "C:/Users/User/Desktop/VLSI_DSP_Notes_HW_Project/hw5/pattern/matrix_dat.txt"
`define Q_GOLDEN  "C:/Users/User/Desktop/VLSI_DSP_Notes_HW_Project/hw5/pattern/q_dat.txt"
`define R_GOLDEN  "C:/Users/User/Desktop/VLSI_DSP_Notes_HW_Project/hw5/pattern/r_dat.txt"


module PATTERN(
    // Output signals
    clk,
    rst_n,
    in_valid,
    in,

    // Input signals
    out_valid,
    out_q,
    out_r
  );
  //================================================================
  //  parameters & integer
  //================================================================
  parameter DATA_WIDTH = 12;
  parameter PATNUM     = 300;
  parameter PAT_COUNTS = 16;
  parameter INTEGER    = 8;
  integer a, c, i, gap, pat_file;
  integer total_cycles;
  integer total_pat;
  integer patcount;
  integer cycles;
  integer addr;
  integer pat_iter;
  integer errors;

  integer color_stage = 0, color, r = 5, g = 0, b = 0;
  //================================================================
  //  INPUT AND OUTPUT DECLARATION
  //================================================================
  output reg clk, rst_n, in_valid;
  output reg [INTEGER-1:0] in;
  input out_valid;
  input [DATA_WIDTH-1:0] out_q,out_r;
  //================================================================
  //  wire & registers
  //================================================================
  reg [INTEGER-1:0] A_GOLDEN[0:PATNUM*PAT_COUNTS-1];
  reg [DATA_WIDTH-1:0] Q_GOLDEN[0:PATNUM*PAT_COUNTS-1];
  reg [DATA_WIDTH-1:0] R_GOLDEN[0:PATNUM*PAT_COUNTS-1];

  reg [DATA_WIDTH-1:0] r_ans_out[0:PATNUM*PAT_COUNTS-1];
  reg [DATA_WIDTH-1:0] q_ans_out[0:PATNUM*PAT_COUNTS-1];

  //================================================================
  //  clock
  //================================================================
  initial
    clk = 0 ;
  always #(`CYCLE_TIME/2.0)  clk = ~clk;
  //================================================================
  //  initial
  //================================================================
  initial
  begin
    //Reading in A
    $readmemb(`A_GOLDEN ,A_GOLDEN);
    //Put golden model in pseudoRAM
    $readmemb(`Q_GOLDEN ,Q_GOLDEN);
    $readmemb(`R_GOLDEN ,R_GOLDEN);

    in_valid = 0 ;
    in = 8'bx ;
    rst_n = 1 ;

    reset_task;
    total_cycles = 0 ;
    total_pat = 0 ;
    errors    = 0 ;

    @(negedge clk);
    for( patcount=0 ; patcount<PATNUM ; patcount=patcount+1 )
    begin

      qr_feed_data_task;

      total_pat = total_pat + 1 ;

      wait_outvalid;
      check_ans;
      delay_task;

      case(color_stage)
        0:
        begin
          r = r - 1;
          g = g + 1;
          if(r == 0)
            color_stage = 1;
        end
        1:
        begin
          g = g - 1;
          b = b + 1;
          if(g == 0)
            color_stage = 2;
        end
        2:
        begin
          b = b - 1;
          r = r + 1;
          if(b == 0)
            color_stage = 0;
        end
      endcase
      color = 16 + r*36 + g*6 + b;
      if(color < 100)
        $display("/033[38;5;%2dmPASS PATTERN NO.%4d/033[00m", color, patcount+1);
      else
        $display("/033[38;5;%3dmPASS PATTERN NO.%4d/033[00m", color, patcount+1);
    end


    #(1000);
    YOU_PASS_task;
    $finish;
  end
  //================================================================
  //  task
  //================================================================
  //================================================================
  //  answer task
  //================================================================
  task check_ans ;
    begin
      if (out_valid===1)
      begin
        cycles   = 0;
        pat_iter = 0;
        while(out_valid===1)
        begin
          cycles = cycles + 1 ;
          if (cycles>16)
          begin
            fail;
            // Spec. 8
            // When out_valid is pulled up and there exists a solution for the grid, out should be correct, and out_valid is limited to be high for 15 cycles.
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            $display ("                                                                SPEC 8 FAIL!                                                                ");
            $display ("                                                 out_valid is limited to be high for 16 cycles.                                             ");
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            repeat(5)  @(negedge clk);
            $finish;
          end

          // Store the result into out_q and out_r, a memory for storing answers.
          addr = patcount * PAT_COUNTS + pat_iter;
          q_ans_out[addr] = out_q;
          r_ans_out[addr] = out_r;

          // check if the answer is correct
          if (r_ans_out[addr] !== R_GOLDEN[addr])
          begin
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            $display ("Pat No: %d",patcount);
            $display ("Pat's iter is %d",pat_iter);
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            $display ("Your answer for R is %b ", out_r);
            $display ("The correct value for R is %b ", R_GOLDEN[addr]);
            // $display("/%d",PATTERN.u_CORDIC.genblk3[0].u_GG.iters_x);
            // $display ("Your answer for R is %b ", out_r);
            // $display ("Data writes into address %d ", addr);
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            // $display ("The correct value for Q is %b ", Q_GOLDEN[addr]);
            // $display ("The correct value for R is %b ", R_GOLDEN[addr]);
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            errors = errors + 1;
          end

          // You have 4800 values. Tolerate 80 errors, I dont know how to calculate differences...
          if(errors > 10)
          begin
            fail;
            // Spec. 8
            // When out_valid is pulled up and there exists a solution for the grid, out should be correct, and out_valid is limited to be high for 15 cycles.
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            $display ("                                                                SPEC 8 FAIL!                                                                ");
            $display ("                                        Number of errors are more than 10, please fix your design!                                          ");
            $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
            repeat(5)  @(negedge clk);
            $finish;
          end

          pat_iter = pat_iter + 1;
          @(negedge clk);
        end
      end

    end
  endtask

  task wait_outvalid;
    begin
      cycles = 0 ;
      while( out_valid!==1 )
      begin
        cycles = cycles + 1 ;
        if (out_q!==0 || out_r !== 0)
        begin
          fail;
          // Spec. 4
          // The out should be reset whenever your out_valid isn’t high.
          $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
          $display ("                                                                SPEC 4 FAIL!                                                                ");
          $display ("                                            The out should be reset whenever your out_valid isn’t high.                                     ");
          $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
          repeat(5)  @(negedge clk);
          $finish;
        end

        @(negedge clk);
      end
      total_cycles = total_cycles + cycles ;
    end
  endtask
  //================================================================
  //  input task
  //================================================================
  task qr_feed_data_task ;
    begin
      in_valid = 1 ;
      for( i=0 ; i<PAT_COUNTS ; i=i+1 )
      begin
        if (out_q!==0 || out_r !== 0)
        begin
          fail;
          // Spec. 4
          // The out should be reset whenever your out_valid isn’t high.
          $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
          $display ("                                                                SPEC 4 FAIL!                                                                ");
          $display ("                                          The out should be reset whenever your out_valid isn’t high.                                       ");
          $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
          repeat(5)  @(negedge clk);
          $finish;
        end
        if (out_valid===1)
        begin
          fail;
          // Spec. 5
          // The out_valid should not overlap with in_valid when in_valid hasn’t been pulled down yet.
          $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
          $display ("                                                                SPEC 5 FAIL!                                                                ");
          $display ("                         The out_valid should not overlap with in_valid when in_valid hasn’t been pulled down yet.                          ");
          $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
          repeat(5)  @(negedge clk);
          $finish;
        end

        addr = patcount * PAT_COUNTS + i;
        in = A_GOLDEN[addr];
        @(negedge clk);
      end
      in_valid = 0 ;
      in = 8'bx ;
    end
  endtask

  task writing_out_data;
  begin

  end
  endtask

  //================================================================
  //  env task
  //================================================================
  task reset_task ;
    begin
      #(`CYCLE_TIME*2);
      rst_n = 0 ;
      #(`CYCLE_TIME*2);
      if ((out_valid!==0)||(out_q!==0) || (out_r !== 0))
      begin
        fail;
        // Spec. 3
        // The reset signal (rst_n) would be given only once at the beginning of simulation.
        // All output signals should be reset after the reset signal is asserted.
        $display ("--------------------------------------------------------------------------------------------------------------------------------------------");
        $display ("                                                                SPEC 3 FAIL!                                                                ");

        $display ("--------------------------------------------------------------------------------------------------------------------------------------------");

        #(100);
        $finish;
      end
      #(1.0);
      rst_n = 1 ;
      #(3.0);
      release clk;
    end
  endtask

  task delay_task ;
    begin
      gap = $urandom_range(1, 5) ;
      repeat(gap) @(negedge clk);
    end
  endtask
  //================================================================
  //  pass/fail task
  //================================================================
  task YOU_PASS_task;
    begin
      // image_.success;
      $display ("----------------------------------------------------------------------------------------------------------------------");
      $display ("                                                  Congratulations!                                                    ");
      $display ("                                           You have passed all patterns!                                              ");
      $display ("                                                                                                                      ");
      $display ("                                        Your execution cycles   = %5d cycles                                          ", total_cycles);
      $display ("                                        Your clock period       = %.1f ns                                             ", `CYCLE_TIME);
      $display ("                                      Average Cycle Per pattern = %.1f ns                                             ", total_cycles/PATNUM);
      $display ("                                        Total latency           = %.1f ns                                             ", (total_cycles + total_pat)*`CYCLE_TIME);
      $display ("----------------------------------------------------------------------------------------------------------------------");

      $finish;
    end
  endtask

  task fail;
    begin
      $display(":( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( FAIL :( ");


      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8Oo::::ooOOO8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o:   ..::..       .:o88@@@@@@@@@@@8OOoo:::..::oooOO8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8.   :8@@@@@@@@@@@@Oo..                   ..:.:..      .:O8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8.  .8@@@@@@@@@@@@@@@@@@@@@@88888888888@@@@@@@@@@@@@@@@@8.    :O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:. .@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8.   :8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O  O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8.   :o@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o  8@@@@@@@@@@@@@8@@@@@@@@8o::o8@@@@@8ooO88@@@@@@@@@@@@@@@@@@@@@@@@8:.  .:ooO8@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o  :@@@@@@@@@@O      :@@@O   ..  :O@@@:       :@@@@OoO8@@@@@@@@@@@@@@@@Oo...     ..:o@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  :8@@@@@@@@@:  .@@88@@@8:  o@@o  :@@@. 0@@@.  O@@@      .O8@@@@@@@@@@@@@@@@@@8OOo.    O8@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  o@@@@@@@@@@O.      :8@8:  o@@O. .@@8  000o  .8@@O  O8O:  .@@o .O@@@@@@@@@@@@@@@@@@@o.  .o@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@. :8@@@@@@@@@@@@@@@:  .o8:  o@@o. .@@O  ::  .O@@@O.  o0o.  :@@O. :8@8::8@@@@@@@@@@@@@@@8O  .:8@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  o8@@@@@@@@@@@OO@@8.  o@8   ''  .O@@o  O@:  :O@@:  ::   .8@@@O. .:   .8@@@@@@@@@@@@@@@@@@O   8@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@. .O@@@@@@@@@@O      .8@@@@Oo::oO@@@@O  8@8:  :@8  :@O. :O@@@@8:   .o@@@@@@@@@@@@@@@@@@@@@@o  :8@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8:  8@@@@@@@@@@@@8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o:8@8:  :@@@@:  .O@@@@@@@@@@@@@@@@@@@@@@@@8:  o@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:  .8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@OoO@@@O  :8@@@@@@@@@@@@@@@@@@@@@@@@@@8o  8@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8.   o8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@88@@@@@@@@@@@@@@@@@@@8::@@@@@88@@@@@@@@@@@@@@@@@@@@@@@  :8@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O.  .:8@@@@@@@@@@@@@@@@@@@88OOoo::....:O88@@@@@@@@@@@@@@@@@@@@8o .8@@@@@@@@@@@@@@@@@@@@@@:  o@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o.   ..:o8888888OO::.      ....:o:..     oO@@@@@@@@@@@@@@@@8O..@@ooO@@@@@@@@@@@@@@@@@@O. :@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@Oo::.          ..:OO@@@@@@@@@@@@@@@@O:  .o@@@@@@@@@@@@@@@@@@@O   8@@@@@@@@@@@@@@@@@. .O@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8O   .8@@@@@@@@@@@@@@@@@@@@@O  O@@@@@@@@@@@@@. o8@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O    .O@@@@@@@@@@@@@@@@@@8..8@@@@@@@@@@@@@. .O@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O:           ..:O88@888@@@@@@@@@@@@@@@@@@@@@@@O  O@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o.                          ..:oO@@@@@@@@@@@@@@@o  @@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.                      .o@@8O::.    o8@@@@@@@@@@@O  8@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o                         :O@@@@@@@o.  :O8@@@@@@@@8  o8@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@88OO888@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8888OOOOO8@@8888@@@@@O.                          .@@@@@@@@@:.  :@@@@@@@@@. .O@");
      $display("@@@@@@@@@@@@@@@@@@@@8o:           O8@@@@@@@@@@@@@@@@@@@8OO:.                     .::                            :8@@@@@@@@@.  .O@@@@@@@o. o@");
      $display("@@@@@@@@@@@@@@@@@@.                 o8@@@@@@@@@@@O:.         .::oOOO8Oo:..::::..                                 o@@@@@@@@@@8:  8@@@@@@o. o@");
      $display("@@@@@@@@@@@@@@@@:                    .@@@@@Oo.        .:OO@@@@@@@@@@@@@@@@@@@@@@@@@o.                            O@@@@@@@@@@@@  o8@@@@@O. o@");
      $display("@@@@@@@@@@@@@@:                       o88.     ..O88@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@888O.                     .8@@@@@@@@@@@@  o8@@@@@: .O@");
      $display("@@@@@@@@@@@@O:                             :o8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:                  .8@@@@@@@@@@@8o  8@@@@@O  O@@");
      $display("@@@@@@@@@@@O.                            :8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o.              :8@@@@@@@@@@8.  .O@@@@o.  :@@@");
      $display("@@@@@@@@@@@:                          :O8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O:          .o@@@@@@@@@8o   .o@@@8:.  .@@@@@");
      $display("@@@@@@@@@@@.                        O8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O.    .o8@@@@@@@@@@O  :O@@8o:   .O@@@@@@@");
      $display("@@@@@@@@@@@.                      :O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O:   o8@@@@@@@@8           oO@@@@@@@@@@");
      $display("@@@@@@@@@@@:                     o@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@.   .@@@@@@@O.      .:o8@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@8o                   8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o   :@@@@O     o8@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@8.               .O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:   .@@@8..:8@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@8:            .o@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O.  :8@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@8O.        8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   :@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@8o   o@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@o   O@@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@O   O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O   :@@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@8   :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:   8@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@8o  :8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:..   .:o@@@@@@@@@@@@@@@@@@8.  O@@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@8o  :8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O.         .:@@@@@@@@@@@@@@@@@:  :O@@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@O.  o@@@@@@@@@@@@@@@@@@@@@@8OOO8@@@@@@@@@@@@@@@@@@@@@@@@@@@8.             .@@@@@@@@@@@@@@@@.  .O@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@o.  .@@@@@@@@@@@@@@@@@@@8:.       :8@@@@@@@@@@@@@@@@@@@@@@@@8.               o8@@@@@@@@@@@@@o. .:@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@o.  :@@@@@@@@@@@@@@@@@O            .@@@@@@@@@@@@@@@@@@@@@@@@@:                .8@@@@@@@@@@@@O.  :@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@O.  .@@@@@@@@@@@@@@@@:             .8@@@@@@@@@@@@@@@@@@@@@@@@O:                o@@@@@@@@@@@@O:  .@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@O.  .@@@@@@@@@@@@@@8:               8@@@@@@@@@@@@@@@@@@@@@@@@@@.               o@@@@@@@@@@@@O:  .@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@O.  .@@@@@@@@@@@@@o.                8@@@@@@@@@@@@@@@@@@@@@@@@@@8o             .8@@@@@@@@@@@@O.  .@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@8:  .@@@@@@@@@@@@@                 :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8:.        O8@@@@@@@@@@@@@@o.  :@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@o   8@@@@@@@@@@@@.               :8@@@@@@@@@          :8@@@@@@@@@@@8OoooO@@@@@@@@@@@@@@@@@@.  .o@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@88O:   O@@@@@@@@@@@@O:             .@@@@@@@@O             .8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8   :8@@@@@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@O:.       :O8@@@@@@@@@@8o           :O@@@@@@@8:             :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8:       :o@@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@o              ..:8@@@@@@@@@8o:::.:O8@@@@@@@@@@@8.           :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O:.             o@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@8o                   :@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@:.     .o@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8                  o8@@@@@@@@@@@@@@@");
      $display("8OOOooooOOoo:.                    :OOOOOOOOOO8888OOOOOOOOOOOoo:ooOOOo: .OOOOOOOOOO888OOooOO888OOOOOooO8:                   .:OOOOOOOOOOO88@@");
      $display("            .                                                                                                                               ");
      $display("@@@@@@@@@@@@@@8o                 .8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8                    :8@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@8O.             o8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@8o                 .@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@::.       :O@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@O..         .:8@@@@@@@@@@@@@@@@@@");
      $display("@@@@@@@@@@@@@@@@@@@@@@@@@88O8@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@88@@@@@@@@@@@@@@@@@@@@@@@@@@");

      // fail_.fail;
    end
  endtask
endmodule
