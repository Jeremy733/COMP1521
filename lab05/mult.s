# COMP1521 18s1 Week 05 Lab
#
# void multMatrices(int n, int m, int p,
#                   int A[n][m], int B[m][p], int C[n][p])
# {
#    for (int r = 0; r < n; r++) {
#       for (int c = 0; c < p; c++) {
#          int sum = 0;
#          for (int i = 0; i < m; i++) {
#             sum += A[r][i] * B[i][c];
#          }
#          C[r][c] = sum;
#       }
#    }
# }

   .text
   .globl multMatrices
multMatrices:
   # possible register usage:
   # n is $s0, m is $s1, p is $s2,
   # r is $s3, c is $s4, i is $s5, sum is $s6
   sw   $fp, -4($sp)
   la   $fp, -4($sp)
   sw   $ra, -4($fp)
   sw   $s0, -8($fp)
   sw   $s1, -12($fp)
   sw   $s2, -16($fp)
   sw   $s3, -20($fp)
   sw   $s4, -24($fp)
   sw   $s5, -28($fp)
   sw   $s6, -32($fp)
   addi $sp, $sp, -36

   # set up stack frame for multMatrices()
   move $s0, $a0
   move $s1, $a1
   move $s2, $a2
   li   $t7, 4			           # sizeof(int)

loop1_init:
   li   $s3, 0
   
loop1_cond:
   bge  $s3, $s0, loop1_end        # r < n

loop2_init:
   li   $s4, 0
   
loop2_cond:
   bge  $s4, $s2, loop2_end
   li   $s6, 0
   
loop3_init:
   li   $s5, 0
   
   # n is $s0, m is $s1, p is $s2,
   # r is $s3, c is $s4, i is $s5, sum is $s6
loop3_cond:
   bge  $s5, $s1, loop3_end
   lw   $t1, 12($fp)               # load A
   lw   $t2, 8($fp)		           # load B
   mul  $t0, $s3, $s1              
   add  $t0, $t0, $s5
   mul  $t0, $t0, $t7
   add  $t1, $t1, $t0
   lw   $t1, ($t1)                 # t1 = A[r][i]
   
   mul  $t0, $s5, $s2
   add  $t0, $t0, $s4
   mul  $t0, $t0, $t7
   add  $t2, $t2, $t0
   lw   $t2, ($t2)                 # t2 = B[i][c]   
   
   mul  $t0, $t1, $t2
   add  $s6, $s6, $t0              # sum += t1 * t2

loop3_step:   
   addi $s5, $s5, 1
   j loop3_cond
   
loop3_end:
   lw   $t3, 4($fp)                # load C
   mul  $t0, $s3, $s2
   add  $t0, $t0, $s4
   mul  $t0, $t0, $t7
   add  $t3, $t3, $t0              # t6 = C[r][c]   

   sw   $s6, ($t3)
   
loop2_step:
   addi $s4, $s4, 1
   j loop2_cond
   
loop2_end:

loop1_step:
   addi $s3, $s3, 1
   j loop1_cond
   
loop1_end:

   # clean up stack and return
   la $sp, 4($fp)
   lw $ra, -4($fp)
   lw $s0, -8($fp)
   lw $s1, -12($fp)
   lw $s2, -16($fp)
   lw $s3, -20($fp)
   lw $s4, -24($fp)
   lw $s5, -28($fp)
   lw $s6, -32($fp)
   lw $fp, ($fp)
   jr $ra

