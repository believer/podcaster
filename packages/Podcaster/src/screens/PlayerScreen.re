open ReactNative;

module PlayState = {
  type t =
    | Loading
    | Playing
    | Paused;

  let toBool =
    fun
    | Playing => false
    | Paused
    | Loading => true;
};

type state = {
  duration: float,
  playbackRate: string,
  playState: PlayState.t,
  position: float,
  isLoaded: bool,
  seekPosition: float,
};

type action('a) =
  | Init(float)
  | SetPlayState(PlayState.t)
  | SetPlaybackRate(string)
  | SetSeekPosition(float);

[@react.component]
let make = (~navigation as _, ~route as _) => {
  let playerRef = React.useRef(Js.Nullable.null);
  let {Player.currentEpisode} = Player.usePlayer();

  let (state, dispatch) =
    React.useReducer(
      (state, action) => {
        switch (action) {
        | Init(duration) => {...state, duration, playState: Paused}

        | SetPlayState(playState) => {...state, playState}

        | SetPlaybackRate(playbackRate) => {...state, playbackRate}

        | SetSeekPosition(position) => {
            ...state,
            position,
            seekPosition: position /. state.duration,
          }
        }
      },
      {
        duration: 0.0,
        playbackRate: "1.0",
        isLoaded: false,
        position: 0.0,
        seekPosition: 0.0,
        playState: Loading,
      },
    );

  switch (currentEpisode) {
  | Some({artwork, url}) =>
    <ScrollView contentContainerStyle=Style.(style(~flexGrow=1., ()))>
      <SafeAreaView style=Style.(style(~flex=1., ()))>
        <View
          style=Style.(
            style(
              ~flex=1.,
              ~paddingHorizontal=32.->dp,
              ~alignItems=`center,
              ~justifyContent=`center,
              (),
            )
          )>
          <Sound.Video
            ref=playerRef
            ignoreSilentSwitch="ignore"
            playInBackground=true
            source={uri: url}
            audioOnly=true
            onLoad={t => {dispatch(Init(t.duration))}}
            onProgress={t => dispatch(SetSeekPosition(t.currentTime))}
            paused={PlayState.toBool(state.playState)}
            rate={
              state.playbackRate
              ->Belt.Float.fromString
              ->Belt.Option.getWithDefault(1.0)
            }
            style=Style.(
              style(~borderRadius=20., ~height=300.->dp, ~width=300.->dp, ())
            )
            poster={artwork->Belt.Option.getWithDefault("")}
          />
          <View style=Style.(style(~width=100.->pct, ()))>
            <CustomSlider
              value={state.seekPosition}
              minimumTrackTintColor="green"
              maximumTrackTintColor="red"
            />
            <Text> {React.string(Duration.make(state.position))} </Text>
            <Text> {React.string(Duration.make(state.duration))} </Text>
            <View
              style=Style.(
                style(
                  ~flexDirection=`row,
                  ~alignItems=`center,
                  ~justifyContent=`center,
                  ~marginTop=24.->dp,
                  (),
                )
              )>
              <TouchableOpacity
                style=Style.(
                  style(
                    ~backgroundColor="#333",
                    ~alignItems=`center,
                    ~justifyContent=`center,
                    ~borderRadius=24.,
                    ~width=48.->dp,
                    ~height=48.->dp,
                    ~marginRight=16.->dp,
                    (),
                  )
                )
                onPress={_ => {
                  switch (playerRef->React.Ref.current->Js.Nullable.toOption) {
                  | Some(player) => player##seek(state.position -. 15.)
                  | None => ()
                  }
                }}>
                <SVGBackward
                  fill="white"
                  width={24.->ReactFromSvg.Size.dp}
                  height={24.->ReactFromSvg.Size.dp}
                />
              </TouchableOpacity>
              {switch (state.playState) {
               | Loading => React.null
               | Paused =>
                 <TouchableOpacity
                   style=Style.(
                     style(
                       ~backgroundColor="#333",
                       ~alignItems=`center,
                       ~justifyContent=`center,
                       ~borderRadius=30.,
                       ~width=60.->dp,
                       ~height=60.->dp,
                       (),
                     )
                   )
                   onPress={_ => dispatch(SetPlayState(Playing))}>
                   <SVGPlay
                     fill="white"
                     width={24.->ReactFromSvg.Size.dp}
                     height={24.->ReactFromSvg.Size.dp}
                   />
                 </TouchableOpacity>
               | Playing =>
                 <TouchableOpacity
                   style=Style.(
                     style(
                       ~backgroundColor="#333",
                       ~alignItems=`center,
                       ~justifyContent=`center,
                       ~borderRadius=30.,
                       ~width=60.->dp,
                       ~height=60.->dp,
                       (),
                     )
                   )
                   onPress={_ => dispatch(SetPlayState(Paused))}>
                   <SVGPause
                     fill="white"
                     width={24.->ReactFromSvg.Size.dp}
                     height={24.->ReactFromSvg.Size.dp}
                   />
                 </TouchableOpacity>
               }}
              <TouchableOpacity
                style=Style.(
                  style(
                    ~backgroundColor="#333",
                    ~alignItems=`center,
                    ~justifyContent=`center,
                    ~borderRadius=24.,
                    ~width=48.->dp,
                    ~height=48.->dp,
                    ~marginLeft=16.->dp,
                    (),
                  )
                )
                onPress={_ => {
                  switch (playerRef->React.Ref.current->Js.Nullable.toOption) {
                  | Some(player) => player##seek(state.position +. 15.)
                  | None => ()
                  }
                }}>
                <SVGForward
                  fill="white"
                  width={24.->ReactFromSvg.Size.dp}
                  height={24.->ReactFromSvg.Size.dp}
                />
              </TouchableOpacity>
            </View>
            <TextInput
              keyboardType=`decimalPad
              placeholder="Playback rate"
              onChangeText={text => dispatch(SetPlaybackRate(text))}
              value={state.playbackRate}
            />
          </View>
        </View>
      </SafeAreaView>
    </ScrollView>
  | None => React.null
  };
};
