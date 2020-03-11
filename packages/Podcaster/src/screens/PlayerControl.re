open ReactNative;

module Size = {
  type t =
    | Small
    | Large;
};

module Control = {
  type t =
    | Play
    | Pause
    | SkipForward
    | SkipBackward;
};

module Icon = {
  let width = 24.->ReactFromSvg.Size.dp;
  let height = 24.->ReactFromSvg.Size.dp;
  let fill = "white";
};

[@react.component]
let make =
    (~size: Size.t=Size.Small, ~onPress, ~control: Control.t, ~disabled=false) => {
  let buttonSize =
    switch (size) {
    | Small => 48.
    | Large => 60.
    };

  <TouchableOpacity
    disabled
    style=Style.(
      style(
        ~backgroundColor={
          disabled ? "#ccc" : "#333";
        },
        ~alignItems=`center,
        ~justifyContent=`center,
        ~borderRadius=buttonSize /. 2.,
        ~width=buttonSize->dp,
        ~height=buttonSize->dp,
        ~marginLeft=16.->dp,
        (),
      )
    )
    onPress>
    {Icon.(
       switch (control) {
       | Control.Play => <SVGPlay fill width height />
       | Pause => <SVGPause fill width height />
       | SkipForward => <SVGForward fill width height />
       | SkipBackward => <SVGBackward fill width height />
       }
     )}
  </TouchableOpacity>;
};
