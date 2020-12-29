# Text-based-User-Interface-photo-editor

Chelcea Claudiu Marian

Contact at: claudiuchelcea01@gmail.com

I created a text editor that supports performing a set of operations over PPM (portable pixmap format) and PGM (portable graymap format) image file formats, both as plain (ASCII) text or binary files.

|      TYPE      |      ASCII      |      BINARY     |             COLORS              |
|  ------------- |   -----------   | --------------- | ------------------------------- |
|    GRAYSCALE   |       P2        |       P5        |  0 - 255 (black & white shade)  |
|    RGB         |       P3        |       P6        |          16.777.216 (RGB)       |


# RUN EXAMPLE: -- where "<" represents keyboard typed command and ">" represents output message.
<LOAD test_file
>Loaded test_file
<SELECT 0 1 8 10
>Selected 0 1 8 10
<CROP
>Image cropped
<SAVE my_binary_file
>Saved my_binary_file
<LOAD non_existent_file
>Failed to load non_existent_file
<LOAD color_file
>Loaded color_file
<GRAYSCALE
>Grayscale filter applied
<SEPIA
>Sepia filter not available
<SAVE my_plain_file ascii
>Saved my_plain_file
<EXIT

# GENERATE YOUR OWN IMAGE:
To generate your own PNM and PGM files, use the "convert" utility that converts png / jpeg / jpg files to these formats:
• Setup: sudo apt install imagemagick
• Documentation: man convert
• Examples:
    convert foo.jpg foo.ppm (transforms foo.jpg în foo.ppm, binary format)
    convert foo.jpg foo.pgm (transforms foo.jpg în foo.pgm, grayscale format)
    convert foo.jpg -compress None foo.ppm (transforms foo.jpg în foo.ppm, plain (ASCII) text format)
    convert foo.jpg -compress None foo.pgm
