/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

//
// Apply Update : out = out + dt*buf
//
#ifdef DIM_1
float linear_interpolate_1D(__global const float *image, float PositionX, int xsize)
{
    /*  Linear interpolation variables */
    int xBas0, xBas1;
    float perc[2]={0, 0};
    float xCom, xComi;
    float color[2]={0, 0};

    /*  Rounded location  */
    float fPositionX;

    /* Determine the coordinates of the pixel(s) which will be come the current pixel */
    /* (using linear interpolation) */
    fPositionX = floor(PositionX);
    xBas0=(int) fPositionX;
    xBas1=xBas0+1;

    /* Linear interpolation constants (percentages) */
    xCom=PositionX-fPositionX;
    xComi=(1-xCom);
    perc[0]=xComi;
    perc[1]=xCom;

    if(xBas0<0) { xBas0=0; if(xBas1<0) { xBas1=0; }}
    if(xBas1>(xsize-1)) { xBas1=xsize-1; if(xBas0>(xsize-1)) { xBas0=xsize-1; }}

    color[0]=image[xBas0];
    color[1]=image[xBas1];
    return color[0]*perc[0]+color[1]*perc[1];
}
#endif

#ifdef DIM_2
float linear_interpolate_2D(__global const float *image, float PositionX, float PositionY, int xsize, int ysize)
{
    /*  Linear interpolation variables */
    int xBas0, xBas1, yBas0, yBas1;
    float perc[4]={0, 0, 0, 0};
    float xCom, yCom, xComi, yComi;
    float color[4]={0, 0, 0, 0};

    /*  Rounded location  */
    float fPositionX, fPositionY;

    /* Determine the coordinates of the pixel(s) which will be come the current pixel */
    /* (using linear interpolation) */
    fPositionX = floor(PositionX); fPositionY = floor(PositionY);
    xBas0=(int) fPositionX; yBas0=(int) fPositionY;
    xBas1=xBas0+1; yBas1=yBas0+1;

    /* Linear interpolation constants (percentages) */
    xCom=PositionX-fPositionX; yCom=PositionY-fPositionY;
    xComi=(1-xCom); yComi=(1-yCom);
    perc[0]=xComi * yComi;
    perc[1]=xComi * yCom;
    perc[2]=xCom * yComi;
    perc[3]=xCom * yCom;

    if(xBas0<0) { xBas0=0; if(xBas1<0) { xBas1=0; }}
    if(yBas0<0) { yBas0=0; if(yBas1<0) { yBas1=0; }}
    if(xBas1>(xsize-1)) { xBas1=xsize-1; if(xBas0>(xsize-1)) { xBas0=xsize-1; }}
    if(yBas1>(ysize-1)) { yBas1=ysize-1; if(yBas0>(ysize-1)) { yBas0=ysize-1; }}

    color[0]=image[xBas0+yBas0*xsize];
    color[1]=image[xBas0+yBas1*xsize];
    color[2]=image[xBas1+yBas0*xsize];
    color[3]=image[xBas1+yBas1*xsize];
    return color[0]*perc[0]+color[1]*perc[1]+color[2]*perc[2]+color[3]*perc[3];
}
#endif

#ifdef DIM_3
float linear_interpolate_3D(__global const float *image, float Tlocalx, float Tlocaly, float Tlocalz, int xsize, int ysize, int zsize)
{
    float Iout;
    /*  Linear interpolation variables */
    int xBas0, xBas1, yBas0, yBas1, zBas0, zBas1;
    float perc[8];
    float xCom, yCom, zCom;
    float xComi, yComi, zComi;
    float color[8]={0, 0, 0, 0, 0, 0, 0, 0};
    float fTlocalx, fTlocaly, fTlocalz;

    fTlocalx=floor(Tlocalx); fTlocaly=floor(Tlocaly); fTlocalz=floor(Tlocalz);

    /* Determine the coordinates of the pixel(s) which will be come the current pixel */
    /* (using linear interpolation) */
    xBas0=(int) fTlocalx; yBas0=(int) fTlocaly; zBas0=(int) fTlocalz;
    xBas1=xBas0+1;      yBas1=yBas0+1;      zBas1=zBas0+1;

    /* Clamp to boundary */
    if(xBas0<0) {xBas0=0; if(xBas1<0) { xBas1=0; }}
    if(yBas0<0) {yBas0=0; if(yBas1<0) { yBas1=0; }}
    if(zBas0<0) {zBas0=0; if(zBas1<0) { zBas1=0; }}
    if(xBas1>(xsize-1)) { xBas1=xsize-1; if(xBas0>(xsize-1)) { xBas0=xsize-1; }}
    if(yBas1>(ysize-1)) { yBas1=ysize-1; if(yBas0>(ysize-1)) { yBas0=ysize-1; }}
    if(zBas1>(zsize-1)) { zBas1=zsize-1; if(zBas0>(zsize-1)) { zBas0=zsize-1; }}

    /*  Get intensities */
#define getcolor_mindex3_float( x, y, z, sizx, sizy, sizz, I) ( I[z*sizx*sizy+y*sizx+x] )
    color[0]=getcolor_mindex3_float(xBas0, yBas0, zBas0, xsize, ysize, zsize, image);
    color[1]=getcolor_mindex3_float(xBas0, yBas0, zBas1, xsize, ysize, zsize, image);
    color[2]=getcolor_mindex3_float(xBas0, yBas1, zBas0, xsize, ysize, zsize, image);
    color[3]=getcolor_mindex3_float(xBas0, yBas1, zBas1, xsize, ysize, zsize, image);
    color[4]=getcolor_mindex3_float(xBas1, yBas0, zBas0, xsize, ysize, zsize, image);
    color[5]=getcolor_mindex3_float(xBas1, yBas0, zBas1, xsize, ysize, zsize, image);
    color[6]=getcolor_mindex3_float(xBas1, yBas1, zBas0, xsize, ysize, zsize, image);
    color[7]=getcolor_mindex3_float(xBas1, yBas1, zBas1, xsize, ysize, zsize, image);

    /* Linear interpolation constants (percentages) */
    xCom=Tlocalx-fTlocalx;  yCom=Tlocaly-fTlocaly;   zCom=Tlocalz-fTlocalz;

    xComi=(1-xCom); yComi=(1-yCom); zComi=(1-zCom);
    perc[0]=xComi * yComi; perc[1]=perc[0] * zCom; perc[0]=perc[0] * zComi;
    perc[2]=xComi * yCom;  perc[3]=perc[2] * zCom; perc[2]=perc[2] * zComi;
    perc[4]=xCom * yComi;  perc[5]=perc[4] * zCom; perc[4]=perc[4] * zComi;
    perc[6]=xCom * yCom;   perc[7]=perc[6] * zCom; perc[6]=perc[6] * zComi;

    /* Set the current pixel value */
    Iout =color[0]*perc[0]+color[1]*perc[1]+color[2]*perc[2]+color[3]*perc[3]+color[4]*perc[4]+color[5]*perc[5]+color[6]*perc[6]+color[7]*perc[7];
    return Iout;
}
#endif

#ifdef DIM_1
float ComputeGradient(__global const IMGPIXELTYPE *img, int xpos, int width)
{
  IMGPIXELTYPE derivative;

  if (xpos <= 0) return 0;
  if (xpos >= width-1) return 0;

  float derivative = (img[xpos+1] - img[xpos-1]) * 0.5;
  return derivative;
}
#endif

#ifdef DIM_2
float2 ComputeGradient(__global const IMGPIXELTYPE *img, int xpos, int ypos, int width, int height)
{
  float2 derivative;
  int gidx = ypos*width + xpos;

  if (xpos <= 0 || xpos >= width-1)
    {
    derivative.x = 0;
    }
  else
    {
    derivative.x = (img[gidx+1] - img[gidx-1]) * 0.5;
    }

  if (ypos <= 0 || ypos >= height-1)
    {
    derivative.y = 0;
    }
  else
    {
    derivative.y = (img[gidx+width] - img[gidx-width]) * 0.5;
    }

  return derivative;
}
#endif

#ifdef DIM_3
float3 ComputeGradient(__global const IMGPIXELTYPE *img, int xpos, int ypos, int zpos, int width, int height, int depth)
{
  float3 derivative;
  int gidx = zpos*width*height + ypos*width + xpos;

  if (xpos <= 0 || xpos >= width-1)
    {
    derivative.x = 0;
    }
  else
    {
    derivative.x = (img[gidx+1] - img[gidx-1]) * 0.5;
    }

  if (ypos <= 0 || ypos >= height-1)
    {
    derivative.y = 0;
    }
  else
    {
    derivative.y = (img[gidx+width] - img[gidx-width]) * 0.5;
    }

  if (zpos <= 0 || zpos >= depth-1)
    {
    derivative.z = 0;
    }
  else
    {
    derivative.z = (img[gidx+width*height] - img[gidx-width*height]) * 0.5;
    }

  return derivative;
}
#endif

#ifdef DIM_1
#define DIM 1
__kernel void ComputeUpdate(__global const IMGPIXELTYPE *fix,
                            __global const IMGPIXELTYPE *mov,
                            __global OUTPIXELTYPE *out,
                            __global BUFPIXELTYPE *buf,
                            float normalizer,
						                int width)
{
  int gix = get_global_id(0);
  OUTPIXELTYPE xwarp;
  OUTPIXELTYPE diff, valueMov, denominator, gradSquare;
  float grad, update;
  int i;

  if(gix < width)
    {
    xwarp = gix + out[gix];

    valueMov = linear_interpolate_1D(mov, xwarp, width);
    diff = fix[gix] - valueMov;

    grad = ComputeGradient(fix, gix, width);
    gradSquare = grad * grad;

    denominator = diff * diff / normalizer + gradSquare;
    update = grad * diff / denominator;

    buf[gix] = update;
    }
}
#endif

#ifdef DIM_2
#define DIM 2
__kernel void ComputeUpdate(__global const IMGPIXELTYPE *fix,
                            __global const IMGPIXELTYPE *mov,
                            __global OUTPIXELTYPE *out,
                            __global BUFPIXELTYPE *buf,
                            float normalizer,
						                int width, int height)
{
  int gix = get_global_id(0);
  int giy = get_global_id(1);
  unsigned int gidx = width*giy + gix;
  unsigned int gidx2 = DIM*gidx;

  OUTPIXELTYPE xwarp, ywarp;
  OUTPIXELTYPE diff, valueMov, denominator, gradSquare;
  float2 grad, update;

  if(gix < width)
    {
    xwarp = gix + out[gidx2];
    ywarp = giy + out[gidx2+1];

    valueMov = linear_interpolate_2D(mov, xwarp, ywarp, width, height);
    diff = fix[gidx] - valueMov;

    grad = ComputeGradient(fix, gix, giy, width, height);
    gradSquare = grad.x * grad.x + grad.y * grad.y;

    denominator = diff * diff / normalizer + gradSquare;
    update.x = grad.x * diff / denominator;
    update.y = grad.y * diff / denominator;

    buf[gidx2]   = grad.x * diff / denominator;
    buf[gidx2+1] = grad.y * diff / denominator;
    }
}
#endif

#ifdef DIM_3
#define DIM 3
__kernel void ComputeUpdate(__global const IMGPIXELTYPE *fix,
                            __global const IMGPIXELTYPE *mov,
                            __global OUTPIXELTYPE *out,
                            __global BUFPIXELTYPE *buf,
                            float normalizer,
						                int width, int height, int depth)
{
  int gix = get_global_id(0);
  int giy = get_global_id(1);
  int giz = get_global_id(2);
  unsigned int gidx = width*height*giz + width*giy + gix;
  unsigned int gidx2 = DIM*gidx;

  OUTPIXELTYPE xwarp, ywarp, zwarp;
  OUTPIXELTYPE diff, valueMov, denominator, gradSquare;
  float3 grad, update;

  if(gix < width)
    {
    xwarp = gix + out[gidx2];
    ywarp = giy + out[gidx2+1];
    zwarp = giz + out[gidx2+2];

    valueMov = linear_interpolate_3D(mov, xwarp, ywarp, zwarp, width, height, depth);
    diff = fix[gidx] - valueMov;

    grad = ComputeGradient(fix, gix, giy, giz, width, height, depth);
    gradSquare = grad.x * grad.x + grad.y * grad.y + grad.z * grad.z;

    denominator = diff * diff / normalizer + gradSquare;

    buf[gidx2]   = grad.x * diff / denominator;
    buf[gidx2+1] = grad.y * diff / denominator;
    buf[gidx2+2] = grad.z * diff / denominator;
    }
}
#endif
