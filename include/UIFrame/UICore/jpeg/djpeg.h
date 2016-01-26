
#include "cdjpeg.h"		/* Common decls for cjpeg/djpeg applications */
#include "jversion.h"		/* for version message */

#include <ctype.h>		/* to declare isprint() */

#ifdef USE_CCOMMAND		/* command-line reader for Macintosh */
#ifdef __MWERKS__
#include <SIOUX.h>              /* Metrowerks needs this */
#include <console.h>		/* ... and this */
#endif
#ifdef THINK_C
#include <console.h>		/* Think declares it here */
#endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

 int Decode (FILE* input_file, long* Image_width, long* Image_height, unsigned short* Image_bpp, unsigned char** p_Dib);

 int DecodeJpegStream(const unsigned char* pMemAddr, int MemSize, long* Image_width, long* Image_height, unsigned short* Image_bpp, unsigned char** p_Dib);
#ifdef __cplusplus
}
#endif