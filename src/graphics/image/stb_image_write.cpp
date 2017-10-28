/* Copyright: stbiw-0.92 - public domain - http://nothings.org/stb/stb_image_write.h
   writes out PNG/BMP/TGA images to C stdio - Sean Barrett 2010
                            no warranty implied; use at your own risk
*/

#include "graphics/image/stb_image_write.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "platform/Platform.h"

namespace stbi {

static int writefv(FILE * f, const char * fmt, ...) {
	
	va_list v;
	va_start(v, fmt);
	
	while(*fmt) {
		switch(*fmt++) {
			case ' ': break;
			case '1': {
				unsigned char x = (unsigned char)va_arg(v, int);
				fputc(x, f);
				break;
			}
			case '2': {
				int x = va_arg(v, int);
				unsigned char b[2] = { (unsigned char)x, (unsigned char)(x >> 8) };
				if(!fwrite(b, 2, 1, f)) {
					return 0;
				}
				break;
			}
			case '4': {
				u32 x = va_arg(v, int);
				unsigned char b[4] = { (unsigned char)x, (unsigned char)(x >> 8),
				                       (unsigned char)(x >> 16), (unsigned char)(x >> 24) };
				if(!fwrite(b, 4, 1, f)) {
					return 0;
				}
				break;
			}
			default: {
				assert(0);
				return 1;
			}
		}
	}
	
	va_end(v);
	
	return 1;
}

static int write3(FILE * f, unsigned char a, unsigned char b, unsigned char c) {
	unsigned char arr[3];
	arr[0] = a, arr[1] = b, arr[2] = c;
	return fwrite(arr, 3, 1, f);
}

static int write_pixels(FILE * f, int x, int y, int comp,
                        const void * data, int write_alpha, int scanline_pad) {
	
	unsigned char bg[3] = { 255, 0, 255 }, px[3];
	u32 zero = 0;
	int i, k;
	
	if(y <= 0) {
		return 1;
	}
	
	for(int j = y - 1; j != -1; j -= 1) {
		
		for(i = 0; i < x; ++i) {
			const unsigned char * d = (const unsigned char *)data + (j * x + i) * comp;
			
			if(write_alpha < 0 && !fwrite(&d[comp - 1], 1, 1, f)) {
				return 0;
			}
			
			switch(comp) {
				case 1:
				case 2: {
					if(!write3(f, d[0], d[0], d[0])) {
						return 0;
					}
					break;
				}
				case 4: {
					if(!write_alpha) {
						// composite against pink background
						for(k = 0; k < 3; ++k) {
							px[k] = bg[k] + ((d[k] - bg[k]) * d[3]) / 255;
						}
						if(!write3(f, px[2], px[1], px[0])) {
							return 0;
						}
						break;
					}
				} /* fall-through */
				case 3: {
					if(!write3(f, d[2], d[1], d[0])) {
						return 0;
					}
					break;
				}
			}
			
			if(write_alpha > 0 && !fwrite(&d[comp - 1], 1, 1, f)) {
				return 0;
			}
			
		}
		
		if(scanline_pad > 0 && !fwrite(&zero, scanline_pad, 1, f)) {
			return 0;
		}
		
	}
	
	return 1;
}


int stbi_write_bmp(char const * filename, int x, int y, int comp, const void * data) {
	
	if(y < 0 || x < 0) {
		return 0;
	}
	
	FILE * f = fopen(filename, "wb");
	if(!f) {
		return 0;
	}
	
	int pad = (-x * 3) & 3;
	int ret = writefv(f, "11 4 22 4" "4 44 22 444444",
	                  'B', 'M', 14 + 40 + (x * 3 + pad) * y, 0, 0, 14 + 40,  // file header
	                  40, x, y, 1, 24, 0, 0, 0, 0, 0, 0);                    // bitmap header);
	if(ret) {
		ret = write_pixels(f, x, y, comp, data, 0, pad);
	}
	
	fclose(f);
	
	return ret;
}

} // namespace stbi
