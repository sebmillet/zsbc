



scale = 20



define e(x) {
  auto  a, b, d, e, f, i, m, n, v, z

  
  
  
  
  
  
  
  
  
  

  
  if (ibase != A) {
     b = ibase;
     ibase = A;
     v = e(x);
     ibase = b;
     return (v);
  }

  
  if (x<0) {
    m = 1
    x = -x
  } 

  
  z = scale;
  n = 6 + z + .44*x;
  scale = scale(x)+1;
  while (x > 1) {
    f += 1;
    x /= 2;
    scale += 1;
  }

  
  scale = n;
  v = 1+x
  a = x
  d = 1

  for (i=2; 1; i++) {
    e = (a *= x) / (d *= i)
    if (e == 0) {
      if (f>0) while (f--)  v = v*v;
      scale = z
      if (m) return (1/v);
      return (v/1);
    }
    v += e
  }
}



define l(x) {
  auto b, e, f, i, m, n, v, z

  
  if (ibase != A) {
     b = ibase;
     ibase = A;
     v = l(x);
     ibase = b;
     return (v);
  }

  
  if (x <= 0) return ((1 - 10^scale)/1)

  
  z = scale;
  scale = 6 + scale;
  f = 2;
  i=0
  while (x >= 2) {  
    f *= 2;
    x = sqrt(x);
  }
  while (x <= .5) {  
    f *= 2;
    x = sqrt(x);
  }

  
  v = n = (x-1)/(x+1)
  m = n*n

  
  for (i=3; 1; i+=2) {
    e = (n *= m) / i
    if (e == 0) {
      v = f*v
      scale = z
      return (v/1)
    }
    v += e
  }
}



define s(x) {
  auto  b, e, i, m, n, s, v, z

  
  if (ibase != A) {
     b = ibase;
     ibase = A;
     v = s(x);
     ibase = b;
     return (v);
  }

  
  z = scale 
  scale = 1.1*z + 2;
  v = a(1)
  if (x < 0) {
    m = 1;
    x = -x;
  }
  scale = 0
  n = (x / v + 2 )/4
  x = x - 4*n*v
  if (n%2) x = -x

  
  scale = z + 2;
  v = e = x
  s = -x*x
  for (i=3; 1; i+=2) {
    e *= s/(i*(i-1))
    if (e == 0) {
      scale = z
      if (m) return (-v/1);
      return (v/1);
    }
    v += e
  }
}


define c(x) {
  auto b, v, z;

  
  if (ibase != A) {
     b = ibase;
     ibase = A;
     v = c(x);
     ibase = b;
     return (v);
  }

  z = scale;
  scale = scale*1.2;
  v = s(x+a(1)*2);
  scale = z;
  return (v/1);
}



define a(x) {
  auto a, b, e, f, i, m, n, s, v, z

  
  
  
  
  
  
  
  
  

  
  if (ibase != A) {
     b = ibase;
     ibase = A;
     v = a(x);
     ibase = b;
     return (v);
  }

  
  m = 1;
  if (x<0) {
    m = -1;
    x = -x;
  }

  
  if (x==1) {
    if (scale <= 25) return (.7853981633974483096156608/m)
    if (scale <= 40) return (.7853981633974483096156608458198757210492/m)
    if (scale <= 60) \
      return (.785398163397448309615660845819875721049292349843776455243736/m)
  }
  if (x==.2) {
    if (scale <= 25) return (.1973955598498807583700497/m)
    if (scale <= 40) return (.1973955598498807583700497651947902934475/m)
    if (scale <= 60) \
      return (.197395559849880758370049765194790293447585103787852101517688/m)
  }


  
  z = scale;

  
   
  if (x > .2)  {
    scale = z+5;
    a = a(.2);
  }
   
  
  scale = z+3;
  while (x > .2) {
    f += 1;
    x = (x-.2) / (1+x*.2);
  }

  
  v = n = x;
  s = -x*x;

  
  for (i=3; 1; i+=2) {
    e = (n *= s) / i;
    if (e == 0) {
      scale = z;
      return ((f*a+v)/m);
    }
    v += e
  }
}



define j(n,x) {
  auto a, b, d, e, f, i, m, s, v, z

  
  if (ibase != A) {
     b = ibase;
     ibase = A;
     v = j(n,x);
     ibase = b;
     return (v);
  }

  
  z = scale;
  scale = 0;
  n = n/1;
  if (n<0) {
    n = -n;
    if (n%2 == 1) m = 1;
  }

  
  f = 1;
  for (i=2; i<=n; i++) f = f*i;
  scale = 1.5*z;
  f = x^n / 2^n / f;

  
  v = e = 1;
  s = -x*x/4
  scale = 1.5*z + length(f) - scale(f);

  
  for (i=1; 1; i++) {
    e =  e * s / i / (n+i);
    if (e == 0) {
       scale = z
       if (m) return (-f*v/1);
       return (f*v/1);
    }
    v += e;
  }
}
