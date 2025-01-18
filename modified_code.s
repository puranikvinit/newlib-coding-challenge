.global memset_mod
memset_mod:
  li t2, 4
  blt a2, t2, zero

  # Prepare word from byte for store word.
  # Initial: 0x 0000 0000 0000 data
  slli t3, a1, 8  # 0x 0000 0000 data 0000
  or t3, t3, a1   # 0x 0000 0000 data data
  mv t4, t3
  slli t3, t3, 16 # 0x data data 0000 0000
  or t3, t3, t4   # 0x data data data data

  # Store words
word:
  sw t3, 0(a0)
  add a2, a2, -4
  add a0, a0, 4
  bge a2, t2, word

zero:
  beqz a2, 2f

  # Store bytes
byte:
  sb a1, 0(a0)
  add a2, a2, -1
  add a0, a0, 1
  bnez a2, byte

2:
  ret


.global memset_bonus
memset_bonus:
  beqz a2, call_st

  # Check if address is word-aligned (last two bits of the address is 0; 0x4 = 0100)
  and t2, a0, 3
  beqz t2, call_st

  # Store byte
  sb a1, 0(a0)
  add a2, a2, -1
  add a0, a0, 1

  j memset_bonus

call_st:
  j memset_mod
