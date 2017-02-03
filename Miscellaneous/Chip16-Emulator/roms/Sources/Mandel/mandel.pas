var
   xPixels, yPixels, xStart, yStart, Xsize, YSize, maxiter : integer;
   xStep, yStep : integer;
   ix,iy,x,y,x0,y0,iteration,xtemp : integer;
   dist : byte;
   temp : byte;
   xx,yy : byte;

begin
  XPixels := 160;
  YPixels := 100;
  XStart := $FF9c;
  YStart := $FFce;
  XSize := 160;
  YSize := 100;
  MaxIter := 16;

  XStep := XSize div XPixels;
  YStep := YSize div YPixels;

  yy := 20;
  For iy := 0 to yPixels do
    begin
          xx := 0;
          For ix := 0 to xPixels do
            begin
               x := xStart + ix * xStep;
               y := yStart + iy * yStep;
               x0 := x;
               y0 := y;
               iteration := 0;
               Repeat
                     xtemp := ((x*x) div 48) - ((y*y) div 48) + x0;
                     y := 2*((x*y) div 48) + y0;
                     x := xtemp;
                     iteration := iteration + 1;
                     dist := ((x*x) div 48) + ((y*y) div 48);
                     If iteration = maxiter then dist := 4000;
               Until dist > 192;

               If iteration <> maxiter then
                If iteration > 1 then
                begin
                 temp := ((iteration shl 4) or iteration) shl 8;
                 temp := temp or ((iteration shl 4) or iteration);
                 DrawSprite(xx,yy,$0201,^temp);
                end;
               xx := xx + 2;
            end;
          yy := yy + 2;
    end;
end.