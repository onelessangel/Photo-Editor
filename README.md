# Text-based-User-Interface-photo-editor

Chelcea Claudiu Marian

Contact at: claudiuchelcea01@gmail.com

I created a text editor that supports performing a set of operations over PPM (portable pixmap format) and PGM (portable graymap format) image file formats, both as plain (ASCII) text or binary files.

|        TYPE        |        ASCII        |        BINARY       |               COLORS                |
| ------------------ | ------------------- | ------------------- | ----------------------------------- |
|      GRAYSCALE     |         P2          |         P5          |    0 - 255 (black & white shade)    |
|      RGB           |         P3          |         P6          |            16.777.216 (RGB)         |


# RUN EXAMPLE: 
-- where "<" represents keyboard typed command and ">" represents output message.
<LOAD test_file  <br/>
>Loaded test_file <br/>
<SELECT 0 1 8 10 <br/>
>Selected 0 1 8 10 <br/>
<CROP<br/>
>Image cropped<br/>
<SAVE my_binary_file<br/>
>Saved my_binary_file<br/>
<LOAD non_existent_file<br/>
>Failed to load non_existent_file<br/>
<LOAD color_file<br/>
>Loaded color_file<br/>
<GRAYSCALE<br/>
>Grayscale filter applied<br/>
<SEPIA<br/>
>Sepia filter not available<br/>
<SAVE my_plain_file ascii<br/>
>Saved my_plain_file<br/>
<EXIT<br/>

# GENERATE YOUR OWN IMAGE:
To generate your own PNM and PGM files, use the "convert" utility that converts png / jpeg / jpg files to these formats:<br/>
• Setup: sudo apt install imagemagick<br/>
• Documentation: man convert<br/>
• Examples:<br/>
    convert foo.jpg foo.ppm (transforms foo.jpg în foo.ppm, binary format)<br/>
    convert foo.jpg foo.pgm (transforms foo.jpg în foo.pgm, grayscale format)<br/>
    convert foo.jpg -compress None foo.ppm (transforms foo.jpg în foo.ppm, plain (ASCII) text format)<br/>
    convert foo.jpg -compress None foo.pgm<br/>
