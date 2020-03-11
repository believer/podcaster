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

  let seek = position => {
    switch (playerRef->React.Ref.current->Js.Nullable.toOption) {
    | Some(player) => player##seek(state.position +. position)
    | None => ()
    };
  };

  switch (currentEpisode) {
  | Some({artwork, url, podcast, title}) =>
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
          <Sound
            ref=playerRef
            uri=url
            onLoad={t => {dispatch(Init(t.duration))}}
            onProgress={t => dispatch(SetSeekPosition(t.currentTime))}
            paused={PlayState.toBool(state.playState)}
            rate={
              state.playbackRate
              ->Belt.Float.fromString
              ->Belt.Option.getWithDefault(1.0)
            }
            poster={artwork->Belt.Option.getWithDefault("")}
          />
          <View style=Style.(style(~marginTop=32.->dp, ()))>
            <Text
              style=Style.(
                textStyle(
                  ~fontSize=21.,
                  ~fontWeight=`_900,
                  ~color="#1C2334",
                  (),
                )
              )>
              {React.string(title)}
            </Text>
            <Text
              style=Style.(
                textStyle(
                  ~fontSize=14.,
                  ~fontWeight=`_300,
                  ~color="#BABDC7",
                  (),
                )
              )>
              {React.string(podcast)}
            </Text>
          </View>
          <View style=Style.(style(~width=100.->pct, ()))>
            <View
              style=Style.(
                style(~flexDirection=`row, ~alignItems=`center, ())
              )>
              <Text style=Style.(style(~color="#1C2334", ~fontSize=12., ()))>
                {React.string(Duration.make(state.position))}
              </Text>
              <View
                style=Style.(style(~flex=1., ~marginHorizontal=16.->dp, ()))>
                <CustomSlider
                  value={state.seekPosition}
                  minimumTrackTintColor="#FF6B7F"
                  maximumTrackTintColor="#FBE0E3"
                />
              </View>
              <Text style=Style.(style(~color="#1C2334", ~fontSize=12., ()))>
                {React.string(Duration.make(state.duration))}
              </Text>
            </View>
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
              <PlayerControl
                control=SkipBackward
                onPress={_ => seek(-15.)}
                disabled={state.playState === Loading}
              />
              {switch (state.playState) {
               | Loading as t
               | Paused as t =>
                 <PlayerControl
                   disabled={t === Loading}
                   control=Play
                   size=Large
                   onPress={_ => dispatch(SetPlayState(Playing))}
                 />
               | Playing =>
                 <PlayerControl
                   control=Pause
                   size=Large
                   onPress={_ => dispatch(SetPlayState(Paused))}
                 />
               }}
              <PlayerControl
                control=SkipForward
                onPress={_ => seek(15.)}
                disabled={state.playState === Loading}
              />
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
