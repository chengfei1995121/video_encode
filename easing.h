/*
--
-- Adapted from
-- Tweener's easing functions (Penner's Easing Equations)
-- and http://code.google.com/p/tweener/ (jstweener javascript version)
--

--[[
Disclaimer for Robert Penner's Easing Equations license:

TERMS OF USE - EASING EQUATIONS

Open source under the BSD License.

Copyright © 2001 Robert Penner
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
    * Neither the name of the author nor the names of contributors may be used to endorse or promote products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
]]

-- For all easing functions:
-- t = elapsed time
-- b = begin
-- c = change == ending - beginning
-- d = duration (total time)
*/
#pragma once

#include <string.h>
#include <math.h>
#include <cstdlib>

#ifndef M_PI
#define M_PI		3.14159265358979323846	/* pi */
#endif

#ifndef M_PI_2
#define M_PI_2		1.57079632679489661923	/* pi/2 */
#endif

#define M_2PI  6.283185307179586

#define DEFAULT_FUNCTION_1PARAM(func,basefunc) \
static inline double func(double t, double b, double c, double d){\
    return basefunc(t,b,c,d,0);\
}

#define DEFAULT_FUNCTION_2PARAM(func,basefunc) \
static inline double func(double t, double b, double c, double d){\
    return basefunc(t,b,c,d,0,0);\
}

static inline double linear(double t, double b, double c, double d){
  return c * t / d + b;
}

static inline double inQuad(double t, double b, double c, double d){
  t = t / d;
  return c * pow(t, 2) + b;
}

static inline double outQuad(double t, double b, double c, double d){
  t = t / d;
  return -c * t * (t - 2) + b;
}

static inline double inOutQuad(double t, double b, double c, double d){
  t = t / d * 2;
  if (t < 1)
    return c / 2 * pow(t, 2) + b;
  else
    return -c / 2 * ((t - 1) * (t - 3) - 1) + b;
}

static inline double outInQuad(double t, double b, double c, double d){
  if (t < d / 2)
    return outQuad (t * 2, b, c / 2, d);
  else
    return inQuad((t * 2) - d, b + c / 2, c / 2, d);
}

static inline double inCubic (double t, double b, double c, double d){
  t = t / d;
  return c * pow(t, 3) + b;
}

static inline double outCubic(double t, double b, double c, double d){
  t = t / d - 1;
  return c * (pow(t, 3) + 1) + b;
}

static inline double inOutCubic(double t, double b, double c, double d){
  t = t / d * 2;
  if (t < 1)
    return c / 2 * t * t * t + b;
  else{
    t = t - 2;
    return c / 2 * (t * t * t + 2) + b;
  }
}

static inline double outInCubic(double t, double b, double c, double d){
  if (t < d / 2)
    return outCubic(t * 2, b, c / 2, d);
  else
    return inCubic((t * 2) - d, b + c / 2, c / 2, d);
}

static inline double inQuart(double t, double b, double c, double d){
  t = t / d;
  return c * pow(t, 4) + b;
}

static inline double outQuart(double t, double b, double c, double d){
  t = t / d - 1;
  return -c * (pow(t, 4) - 1) + b;
}

static inline double inOutQuart(double t, double b, double c, double d){
  t = t / d * 2;
  if (t < 1)
    return c / 2 * pow(t, 4) + b;
  else{
    t = t - 2;
    return -c / 2 * (pow(t, 4) - 2) + b;
  }
}

static inline double outInQuart(double t, double b, double c, double d){
  if (t < d / 2)
    return outQuart(t * 2, b, c / 2, d);
  else
    return inQuart((t * 2) - d, b + c / 2, c / 2, d);
}

static inline double inQuint(double t, double b, double c, double d){
  t = t / d;
  return c * pow(t, 5) + b;
}

static inline double outQuint(double t, double b, double c, double d){
  t = t / d - 1;
  return c * (pow(t, 5) + 1) + b;
}

static inline double inOutQuint(double t, double b, double c, double d){
  t = t / d * 2;
  if (t < 1)
    return c / 2 * pow(t, 5) + b;
  else{
    t = t - 2;
    return c / 2 * (pow(t, 5) + 2) + b;
  }
}

static inline double outInQuint(double t, double b, double c, double d){
  if (t < d / 2)
    return outQuint(t * 2, b, c / 2, d);
  else
    return inQuint((t * 2) - d, b + c / 2, c / 2, d);
}

static inline double inSine(double t, double b, double c, double d){
  return -c * cos(t / d * M_PI_2) + c + b;
}

static inline double outSine(double t, double b, double c, double d){
  return c * sin(t / d * M_PI_2) + b;
}

static inline double inOutSine(double t, double b, double c, double d){
  return -c / 2 * (cos(M_PI * t / d) - 1) + b;
}

static inline double outInSine(double t, double b, double c, double d){
  if (t < d / 2)
    return outSine(t * 2, b, c / 2, d);
  else
    return inSine((t * 2) -d, b + c / 2, c / 2, d);
}

static inline double inExpo(double t, double b, double c, double d){
  if (t == 0)
    return b;
  else
    return c * pow(2, 10 * (t / d - 1)) + b - c * 0.001;
}

static inline double outExpo(double t, double b, double c, double d){
  if (t == d)
    return b + c;
  else
    return c * 1.001 * (-pow(2, -10 * t / d) + 1) + b;
}

static inline double inOutExpo(double t, double b, double c, double d){
  if (t == 0)
      return b;
  if (t == d)
      return b + c;

  t = t / d * 2;
  if (t < 1)
    return c / 2 * pow(2, 10 * (t - 1)) + b - c * 0.0005;
  else{
    t = t - 1;
    return c / 2 * 1.0005 * (-pow(2, -10 * t) + 2) + b;
  }
}

static inline double outInExpo(double t, double b, double c, double d){
  if (t < d / 2)
    return outExpo(t * 2, b, c / 2, d);
  else
    return inExpo((t * 2) - d, b + c / 2, c / 2, d);
}

static inline double inCirc(double t, double b, double c, double d){
  t = t / d;
  return (-c * (sqrt(1 - pow(t, 2)) - 1) + b);
}

static inline double outCirc(double t, double b, double c, double d){
  t = t / d - 1;
  return (c * sqrt(1 - pow(t, 2)) + b);
}

static inline double inOutCirc(double t, double b, double c, double d){
  t = t / d * 2;
  if (t < 1)
    return -c / 2 * (sqrt(1 - t * t) - 1) + b;
  else{
    t = t - 2;
    return c / 2 * (sqrt(1 - t * t) + 1) + b;
  }
}

static inline double outInCirc(double t, double b, double c, double d){
  if (t < d / 2)
    return outCirc(t * 2, b, c / 2, d);
  else
    return inCirc((t * 2) - d, b + c / 2, c / 2, d);
}

static inline double inElastic_p(double t, double b, double c, double d, double a, double p){
  if (t == 0)
    return b;

  t = t / d;

  if (t == 1)
    return b + c;

  if (p == 0)
      p = d * 0.3;

  double s;

  if ( a == 0 || a < abs(c)){
    a = c;
    s = p / 4;
  }
  else{
    s = p / M_2PI * asin(c/a);
  }

  t = t - 1;

  return -(a * pow(2, 10 * t) * sin((t * d - s) * M_2PI / p)) + b;
}

DEFAULT_FUNCTION_2PARAM(inElastic,inElastic_p)

static inline double outElastic_p(double t, double b, double c, double d, double a, double p){
  if (t == 0)
      return b;

  t = t / d;

  if (t == 1)
      return b + c;

  if (p == 0)
      p = d * 0.3;

  double s;

  if (a == 0 || a < abs(c)){
    a = c;
    s = p / 4;
  }
  else{
    s = p / M_2PI * asin(c/a);
  }

  return a * pow(2, -10 * t) * sin((t * d - s) * M_2PI / p) + c + b;
}
DEFAULT_FUNCTION_2PARAM(outElastic,outElastic_p)

static inline double inOutElastic_p(double t, double b, double c, double d, double a, double p){
  if (t == 0)
      return b;

  t = t / d * 2;

  if (t == 2)
      return b + c;

  if (p == 0)
      p = d * (0.3 * 1.5);

  //emmmm, code from lua a maybe nil
  if (a == 0)
      a = 0;

  double s;

  if (a == 0 || a < abs(c)){
    a = c;
    s = p / 4;
  }
  else{
    s = p / M_2PI * asin(c / a);
  }

  if (t < 1){
    t = t - 1;
    return -0.5 * (a * pow(2, 10 * t) * sin((t * d - s) * M_2PI / p)) + b;
  }
  else{
    t = t - 1;
    return a * pow(2, -10 * t) * sin((t * d - s) * M_2PI / p ) * 0.5 + c + b;
  }
}

DEFAULT_FUNCTION_2PARAM(inOutElastic,inOutElastic_p)

static inline double outInElastic_p(double t, double b, double c, double d, double a, double p){
  if (t < d / 2)
    return outElastic_p(t * 2, b, c / 2, d, a, p);
  else
    return inElastic_p((t * 2) - d, b + c / 2, c / 2, d, a, p);
}

DEFAULT_FUNCTION_2PARAM(outInElastic,outInElastic_p)

static inline double inBack_p(double t, double b, double c, double d, double s){
  if (s == 0)
      s = 1.70158;

  t = t / d;
  return c * t * t * ((s + 1) * t - s) + b;
}
DEFAULT_FUNCTION_1PARAM(inBack,inBack_p)

static inline double outBack_p(double t, double b, double c, double d, double s){
  if (s == 0)
      s = 1.70158;

  t = t / d - 1;
  return c * (t * t * ((s + 1) * t + s) + 1) + b;
}
DEFAULT_FUNCTION_1PARAM(outBack,outBack_p)

static inline double inOutBack_p(double t, double b, double c, double d, double s){
  if (s == 0)
      s = 1.70158;

  s = s * 1.525;
  t = t / d * 2;
  if (t < 1)
    return c / 2 * (t * t * ((s + 1) * t - s)) + b;
  else{
    t = t - 2;
    return c / 2 * (t * t * ((s + 1) * t + s) + 2) + b;
  }
}
DEFAULT_FUNCTION_1PARAM(inOutBack,inOutBack_p)

static inline double outInBack_p(double t, double b, double c, double d, double s){
  if (t < d / 2)
    return outBack_p(t * 2, b, c / 2, d, s);
  else
    return inBack_p((t * 2) - d, b + c / 2, c / 2, d, s);
}
DEFAULT_FUNCTION_1PARAM(outInBack,outInBack_p)

static inline double outBounce(double t, double b, double c, double d){
  t = t / d;
  if (t < 1 / 2.75)
    return c * (7.5625 * t * t) + b;
  else if (t < 2 / 2.75){
    t = t - (1.5 / 2.75);
    return c * (7.5625 * t * t + 0.75) + b;
  }
  else if (t < 2.5 / 2.75){
    t = t - (2.25 / 2.75);
    return c * (7.5625 * t * t + 0.9375) + b;
  }
  else{
    t = t - (2.625 / 2.75);
    return c * (7.5625 * t * t + 0.984375) + b;
  }
}

static inline double inBounce(double t, double b, double c, double d){
  return c - outBounce(d - t, 0, c, d) + b;
}

static inline double inOutBounce(double t, double b, double c, double d){
  if (t < d / 2)
    return inBounce(t * 2, 0, c, d) * 0.5 + b;
  else
    return outBounce(t * 2 - d, 0, c, d) * 0.5 + c * .5 + b;
}

static inline double outInBounce(double t, double b, double c, double d){
  if (t < d / 2)
    return outBounce(t * 2, b, c / 2, d);
  else
    return inBounce((t * 2) - d, b + c / 2, c / 2, d);
}


typedef double (*easingFunction)(double t, double b, double c, double d);

static const uint8_t easingCount = 41;

typedef enum{
    kLinear      ,
    kInQuad      ,
    kOutQuad     ,
    kInOutQuad   ,
    kOutInQuad   ,
    kInCubic     ,
    kOutCubic    ,
    kInOutCubic  ,
    kOutInCubic  ,
    kInQuart     ,
    kOutQuart    ,
    kInOutQuart  ,
    kOutInQuart  ,
    kInQuint     ,
    kOutQuint    ,
    kInOutQuint  ,
    kOutInQuint  ,
    kInExpo      ,
    kOutExpo     ,
    kInOutExpo   ,
    kOutInExpo   ,
    kInSine      ,
    kOutSine     ,
    kInOutSine   ,
    kOutInSine   ,
    kInCirc      ,
    kOutCirc     ,
    kInOutCirc   ,
    kOutInCirc   ,
    kInBack      ,
    kOutBack     ,
    kInOutBack   ,
    kOutInBack   ,
    kInBounce    ,
    kOutBounce   ,
    kInOutBounce ,
    kOutInBounce ,
    kInElastic   ,
    kOutElastic  ,
    kInOutElastic,
    kOutInElastic,

}FunctionType;

struct EasingFunctionDefine{
    FunctionType    type;
    const char*     name;
    easingFunction  function;
};

static EasingFunctionDefine easingFunctions[easingCount] ={
    {kLinear      ,"linear"         ,linear      },
    {kInQuad      ,"inQuad"         ,inQuad      },
    {kOutQuad     ,"outQuad"        ,outQuad     },
    {kInOutQuad   ,"inOutQuad"      ,inOutQuad   },
    {kOutInQuad   ,"outInQuad"      ,outInQuad   },
    {kInCubic     ,"inCubic"        ,inCubic     },
    {kOutCubic    ,"outCubic"       ,outCubic    },
    {kInOutCubic  ,"inOutCubic"     ,inOutCubic  },
    {kOutInCubic  ,"outInCubic"     ,outInCubic  },
    {kInQuart     ,"inQuart"        ,inQuart     },
    {kOutQuart    ,"outQuart"       ,outQuart    },
    {kInOutQuart  ,"inOutQuart"     ,inOutQuart  },
    {kOutInQuart  ,"outInQuart"     ,outInQuart  },
    {kInQuint     ,"inQuint"        ,inQuint     },
    {kOutQuint    ,"outQuint"       ,outQuint    },
    {kInOutQuint  ,"inOutQuint"     ,inOutQuint  },
    {kOutInQuint  ,"outInQuint"     ,outInQuint  },
    {kInExpo      ,"inExpo"         ,inExpo     },
    {kOutExpo     ,"outExpo"        ,outExpo     },
    {kInOutExpo   ,"inOutExpo"      ,inOutExpo   },
    {kOutInExpo   ,"outInExpo"      ,outInExpo   },
    {kInSine      ,"inSine"         ,inSine      },
    {kOutSine     ,"outSine"        ,outSine     },
    {kInOutSine   ,"inOutSine"      ,inOutSine   },
    {kOutInSine   ,"outInSine"      ,outInSine   },
    {kInCirc      ,"inCirc"         ,inCirc      },
    {kOutCirc     ,"outCirc"        ,outCirc     },
    {kInOutCirc   ,"inOutCirc"      ,inOutCirc   },
    {kOutInCirc   ,"outInCirc"      ,outInCirc   },
    {kInBack      ,"inBack"         ,inBack      },
    {kOutBack     ,"outBack"        ,outBack     },
    {kInOutBack   ,"inOutBack"      ,inOutBack   },
    {kOutInBack   ,"outInBack"      ,outInBack   },
    {kInBounce    ,"inBounce"       ,inBounce    },
    {kOutBounce   ,"outBounce"      ,outBounce   },
    {kInOutBounce ,"inOutBounce"    ,inOutBounce },
    {kOutInBounce ,"outInBounce"    ,outInBounce },
    {kInElastic   ,"inElastic"      ,inElastic   },
    {kOutElastic  ,"outElastic"     ,outElastic  },
    {kInOutElastic,"inOutElastic"	,inOutElastic},
    {kOutInElastic,"outInElastic"	,outInElastic},
};

static inline EasingFunctionDefine* getEasingFunctionFromType(FunctionType type){
    return &easingFunctions[(int)type];
}

static inline EasingFunctionDefine* getEasingFunctionFromName(const char* name){
    for(int index = 0; index < easingCount; index++){
        if(strcmp(name,easingFunctions[index].name) == 0){
            return &easingFunctions[index];
        }
    }
    return &easingFunctions[0];
}
