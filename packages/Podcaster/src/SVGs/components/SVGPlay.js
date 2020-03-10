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
<Svg viewBox="0 0 20 20" width={width} height={height} fill={fill}><Path d="M4 4l12 6-12 6z"/></Svg>

  );
};
