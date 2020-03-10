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
<Svg viewBox="0 0 64 64" ariaMabelledby="title" ariaDescribedby="desc" width={width} height={height} fill={fill}><Path data-name="layer1"  stroke="#202020" stroke-miterlimit="10" stroke- d="M5 32l32-22v13.8L57 10v44L37 40.2V54L5 32z" strokeMinejoin="round" strokeMinecap="round"/></Svg>

  );
};
