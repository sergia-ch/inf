x0=0.2050
x1=0.2052
x2=0.2060
x3=0.2065
x4=0.2069
x5=0.2075

y0=0.20792
y1=0.20813
y2=0.20896
y3=0.20949
y4=0.20990
y5=0.21053

x=0.2062

#print y2*(x-x3)*(x-x4)/(x2-x3)/(x2-x4)+y3*(x-x2)*(x-x4)/(x3-x2)/(x3-x4)+y4*(x-x2)*(x-x3)/(x4-x2)/(x4-x3)
print y2*(x-x3)*(x-x4)*(x-x5)/(x2-x3)/(x2-x4)/(x2-x5)+y3*(x-x2)*(x-x4)*(x-x5)/(x3-x2)/(x3-x4)/(x3-x5)+y4*(x-x2)*(x-x3)*(x-x5)/(x4-x2)/(x4-x3)/(x4-x5)+y5*(x-x2)*(x-x3)*(x-x4)/(x5-x2)/(x5-x3)/(x5-x4)
