import React from 'react';
import Svg, {
  Circle,
  Ellipse,
  G,
  Text,
  TSpan as Tspan,
  TextPath,
  Path,
  Polygon,
  Polyline,
  Line,
  Rect,
  Use,
  Image,
  Symbol,
  Defs,
  LinearGradient,
  RadialGradient,
  Stop,
  ClipPath,
  Pattern,
  Mask,
} from 'react-native-svg';

export default ({width, height, fill}) => {
  return (
<Svg viewBox="0 0 64 64" ariaMabelledby="title" ariaDescribedby="desc" width={width} height={height} fill={fill}><Path data-name="layer1"  stroke="#202020" stroke-miterlimit="10" stroke- d="M58 32L26 10v13.8L6 10v44l20-13.8V54l32-22z" strokeMinejoin="round" strokeMinecap="round"/></Svg>

  );
};
