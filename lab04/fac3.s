# COMP1521 18s2 Week 04 Lab
# Compute factorials, recursive function


### Global data

   .data
msg1:
   .asciiz "n  = "
msg2:
   .asciiz "n! = "
eol:
   .asciiz "\n"

### main() function
   .text
   .globl main
main:
   #  set up stack frame
   sw    $fp, -4($sp)       # push $fp onto stack
   la    $fp, -4($sp)       # set up $fp for this function
   sw    $ra, -4($fp)       # save return address
   sw    $s0, -8($fp)       # save $s0 to use as ... int n;
   addi  $sp, $sp, -12      # reset $sp to last pushed item

   #  code for main()
   li    $s0, 0             # n = 0;
   
   la    $a0, msg1
   li    $v0, 4
   syscall                  # printf("n  = ");

   li    $v0, 5
   syscall
   move  $s0, $v0             # scanf("%d", $n);
   
   la    $a0, msg2
   li    $v0, 4
   syscall                  # printf("n! = ");
   
   move  $a0, $s0
   jal   fac                # fac(n)
   
   move  $a0, $v0
   li    $v0, 1
   syscall                  # printf("%d", fac(n));
   
   la    $a0, eol
   li    $v0, 4
   syscall                  # printf("\n");


   # clean up stack frame
   lw    $s0, -8($fp)       # restore $s0 value
   lw    $ra, -4($fp)       # restore $ra for return
   la    $sp, 4($fp)        # restore $sp (remove stack frame)
   lw    $fp, ($fp)         # restore $fp (remove stack frame)

   li    $v0, 0
   jr    $ra                # return 0

# fac() function

fac:
   # set up stack frame
   sw    $fp, -4($sp)       # push $fp onto stack
   la    $fp, -4($sp)       # set up $fp for this function
   sw    $ra, -4($fp)       # save return address
   sw    $s0, -8($fp)       # save $s0 to use as ... int n;
   addi  $sp, $sp, -12      # reset $sp to last pushed item

   # code for fac()
   move $s0, $a0
   
   base:
       li	 $t0, 1 		
       bgt	 $s0, $t0, recursion
       						# if n > 1
       li	 $v0, 1
       j post
   
   recursion:
   	   addi  $t1, $s0, -1	# n--;
   	   move  $a0, $t1
   	   jal fac				# fac(n-1);
   	   mul	 $v0, $s0, $v0	# n*fac(n-1);
   
   post:

   # clean up stack frame
   lw    $s0, -8($fp)       # restore $s0 value
   lw    $ra, -4($fp)       # restore $ra for return
   la    $sp, 4($fp)        # restore $sp (remove stack frame)
   lw    $fp, ($fp)         # restore $fp (remove stack frame)

   jr    $ra                # return 0

