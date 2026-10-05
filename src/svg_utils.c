#include "svg_utils.h"
#include <stdio.h>
#include <string.h>

char*
txt_align_to_char(txtAlign a)
{
    switch(a)
    {
        case TXT_MIDDLE:
            return "middle";
        case TXT_RIGHT:
            return "end";
        default:
            return "begin";
    }
}

char*
txt_style_to_char(txtStyle a)
{
   switch(a)
    {
        case TXT_BOLD:
            return "bold";
        default:
            return "regular";
    }
}


void
svg_header(char*  buffer,
           unsigned int width,
           unsigned int height)
{
    sprintf(buffer,
            "<svg class=\"charter\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"100%%\" viewbox=\"0 0 %u %u\">\n",
            width, height);
}

void
svg_footer(char* buffer)
{
    sprintf(buffer + strlen(buffer), "</svg>\n" );
}

void
clip_region(char*  buffer,
             double x,
             double y,
             double width,
             double height,
             char*  id)
{
    sprintf(buffer + strlen(buffer), "<defs>"
            "<clipPath id=\"%s\">"
            "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\"/>\n"
            "</clipPath>"
            "</defs>",
            id, x, y, width, height);
}

void
rect(char*  buffer,
     double x,
     double y,
     double width,
     double heigth,
     char*  fill,
     char*  stroke,
     double stroke_width,
     char*  clip_id)
{
    rect_alpha(buffer,x , y, width, heigth, fill, 1.0, stroke, stroke_width, clip_id);
}

void
rect_alpha(char*  buffer,
           double x,
           double y,
           double width,
           double heigth,
           char*  fill,
           double fill_alpha,
           char*  stroke,
           double stroke_width,
           char*  clip_id)
{
    if (clip_id)
    {
        sprintf(buffer + strlen(buffer), "<rect clip-path=\"url(#%s)\" ",
                clip_id);
    }else
    {
        sprintf(buffer + strlen(buffer), "<rect " );
    }
    sprintf(buffer + strlen(buffer),
            " x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" "
            "style=\"fill:%s; fill-opacity:%.2f; stroke:%s; stroke-width:%.2f;\" />\n",
            x, y, width, heigth, fill, fill_alpha, stroke, stroke_width);
}

void
line(char*  buffer,
     double x1,
     double y1,
     double x2,
     double y2,
     char*  color,
     double line_width,
     char*  clip_id)
{
    styled_line(buffer, x1, y1, x2, y2, color, line_width, "", clip_id);
}

void
styled_line(char*  buffer,
             double x1,
             double y1,
             double x2,
             double y2,
             char*  color,
             double line_width,
             char*  style,
             char*  clip_id)
{
    if (clip_id)
    {
       sprintf(buffer + strlen(buffer), "<line clip-path=\"url(#%s)\" ", clip_id);
    } else
    {
      sprintf(buffer + strlen(buffer), "<line " );
    }
    sprintf(buffer + strlen(buffer),
            " x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" %s style=\"stroke: %s;stroke-width:%.2f\"/>\n",
                x1, y1, x2, y2, style, color, line_width);
}


void
poly_line(char*         buffer,
          double*       xs,
          double*       ys,
          unsigned int  n,
          char*         color,
          double        line_width,
          char*         style,
          char*         clip_id)
{
    if (clip_id)
    {
        sprintf(buffer + strlen(buffer), "<polyline clip-path=\"url(#%s)\"", clip_id);
    }else
    {
        sprintf(buffer + strlen(buffer), "<polyline " );
    }
    sprintf(buffer + strlen(buffer), " style=\"fill:none; stroke:%s; stroke-width:%.2f;\" %s points=\"",
                color, line_width, style);

    unsigned int i;
    for (i = 0;i < n; i++)
    {
        sprintf(buffer + strlen(buffer), "%.2f,%.2f ", xs[i], ys[i]);
    }
    sprintf(buffer + strlen(buffer), "\" />" );
}


void
text_transform(char*      buffer,
               double     x,
               double     y,
               txtAlign   anchor,
               txtStyle   style,
               char*      transform,
               char*      txt,
               char*      clip_id)
{
    if (clip_id)
    {
        sprintf(buffer + strlen(buffer), "<text clip-path=\"url(#%s)\" ", clip_id);
    }else
    {
        sprintf(buffer + strlen(buffer), "<text " );
    }
    if (transform)
    {
        sprintf(buffer + strlen(buffer), " transform=\"%s\" ", transform);
    }

    sprintf(buffer + strlen(buffer),
            " x=\"%.2f\" y=\"%.2f\" text-anchor=\"%s\"  font-weight=\"%s\">%s</text>\n",
            x, y, txt_align_to_char(anchor), txt_style_to_char(style), txt);
}

void
text(char*      buffer,
     double     x,
     double     y,
     txtAlign   anchor,
     txtStyle   style,
     char*      txt,
     char*      clip_id)
{
    text_transform(buffer, x, y, anchor, style, NULL, txt, clip_id);
}

void
bold_text(char*     buffer,
          double    x,
          double    y,
          txtAlign  anchor,
          char*     txt,
          char*     clip_id)
{
    text(buffer, x, y, anchor, TXT_BOLD, txt, clip_id);
}

void
regular_text(char*     buffer,
             double    x,
             double    y,
             txtAlign  anchor,
             char*     txt,
             char*     clip_id)
{
    text(buffer, x, y, anchor, TXT_NORMAL, txt, clip_id);
}


void
circle(char*  buffer,
       double x,
       double y,
       double r,
       char*  color,
       char*  clip_id)
{

    sprintf(buffer + strlen(buffer), "<circle" );
    if (clip_id)
    {
        sprintf(buffer + strlen(buffer), " clip-path=\"url(#%s)\" ",
                        clip_id);
    }
    sprintf(buffer + strlen(buffer), " cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" fill=\"%s\" />",
                    x, y, r, color);

}
