#include "PlateCarreeProjection.h"
namespace cowisprojections {
PlateCarreeProjection::PlateCarreeProjection():MinLatitude(-85.05112878), MaxLatitude(85.05112878),MinLongitude(-180),
MaxLongitude(180), tileSize(512, 512)
{

}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
Size PlateCarreeProjection::TileSize() const
{
    return tileSize;
}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
double PlateCarreeProjection::Axis() const
{
    return 6378137;
}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
double PlateCarreeProjection::Flattening() const
{
    return (1.0 / 298.257223563);
}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
Point PlateCarreeProjection::FromLatLngToPixel(double lat, double lng, const int &zoom)
{
    Point ret;
    lat = Clip(lat, MinLatitude, MaxLatitude);
    lng = Clip(lng, MinLongitude, MaxLongitude);

    Size s = GetTileMatrixSizePixel(zoom);
    double mapSizeX = s.Width();
    //double mapSizeY = s.Height();
    double scale = 360.0 / mapSizeX;

    ret.setX((int) ((90.0 - lat) / scale));
    ret.setY((int) ((lng + 180.0) / scale));
    return ret;
}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
cowisinternals::PointLatLng PlateCarreeProjection::FromPixelToLatLng(const int &x, const int &y, const int &zoom)
{
    cowisinternals::PointLatLng ret;
    Size s = GetTileMatrixSizePixel(zoom);
    double mapSizeX = s.Width();
    double scale = 360.0 / mapSizeX;
    ret.setLat(90 - (y * scale));
    ret.setLng((x * scale) - 180);
    return ret;
}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
Size PlateCarreeProjection::GetTileMatrixMinXY(const int &zoom)
{
    Q_UNUSED(zoom)
    return Size(0 , 0);
}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
Size PlateCarreeProjection::GetTileMatrixMaxXY(const int &zoom)
{
    int y = (int) pow(2.0f, zoom);
    return Size((2 * y) - 1, y - 1);
}
/********************************************************************************
* @version   1.0
* @parameter
* @Function:
* @return
*******************************************************************************/
double PlateCarreeProjection::Clip(const double &n, const double &minValue, double maxValue)
{
    return qMin(qMax(n, minValue), maxValue);
}
}


