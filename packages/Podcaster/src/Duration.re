[@bs.module "track-duration"] external parse: float => string = "parse";

let make = seconds => parse(seconds *. 1000.);
