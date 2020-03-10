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
<Svg viewBox="0 0 20 20" width={width} height={height} fill={fill}><Path d="M5 4h3v12H5V4zm7 0h3v12h-3V4z"/></Svg>

  );
};
