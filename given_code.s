.global memset_given
memset_given:
  mv t1, a0
  beqz a2, 2f
 
1:
  sb a1, 0(t1)
  add a2, a2, -1
  add t1, t1, 1
  bnez a2, 1b
 
2:
  ret
