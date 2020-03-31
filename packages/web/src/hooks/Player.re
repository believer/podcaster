module PlayState = {
  type t =
    | Ready({
        player: Audio.t,
        duration: float,
      })
    | Loading
    | NoTrack;
};

module CurrentTrack = {
  type t = {
    cover: option(string),
    description: string,
    title: string,
    url: string,
  };

  let make = (episode, cover) => {
    cover,
    description: episode##description,
    title: episode##title,
    url: episode##url,
  };
};

module Context = {
  type t = {
    currentTrack: option(CurrentTrack.t),
    playState: PlayState.t,
    playbackRate: float,
    setCurrentTrack:
      (
        {
          .
          "description": string,
          "url": string,
          "title": string,
          "id": string,
        },
        option(string)
      ) =>
      unit,
    setPlaybackRate: float => unit,
  };

  include ReactContext.Make({
    type context = t;

    let defaultValue = {
      currentTrack: None,
      playbackRate: 1.0,
      playState: PlayState.Loading,
      setCurrentTrack: (_, _) => (),
      setPlaybackRate: _ => (),
    };
  });
};

module Provider = {
  type state = {
    currentTrack: option(CurrentTrack.t),
    playState: PlayState.t,
    playbackRate: float,
  };

  type action =
    | SetPlaybackRate(float)
    | SetPlayState(PlayState.t)
    | SetCurrentTrack(option(CurrentTrack.t));

  [@react.component]
  let make = (~children) => {
    let (state, dispatch) =
      React.useReducer(
        (state, action) => {
          switch (action) {
          | SetPlaybackRate(playbackRate) => {...state, playbackRate}
          | SetCurrentTrack(currentTrack) => {...state, currentTrack}
          | SetPlayState(playState) => {...state, playState}
          }
        },
        {currentTrack: None, playbackRate: 1.0, playState: PlayState.Loading},
      );

    React.useEffect1(
      () => {
        switch (state.currentTrack) {
        | None =>
          dispatch(SetPlayState(NoTrack));
          None;

        | Some({url}) =>
          let player = Audio.make(url);

          let canPlay = _event => {
            dispatch(
              SetPlayState(
                Ready({player, duration: player.duration *. 1000.}),
              ),
            );
          };

          player->Audio.addListener("canplay", canPlay);

          Some(
            _ => {
              player->Audio.pause;
              player->Audio.removeListener("canplay", canPlay);
            },
          );
        }
      },
      [|state.currentTrack|],
    );

    let setCurrentTrack = (episode, cover) => {
      dispatch(SetCurrentTrack(Some(CurrentTrack.make(episode, cover))));
    };

    let setPlaybackRate = playbackRate => {
      dispatch(SetPlaybackRate(playbackRate));
    };

    <Context.Provider
      value={
        currentTrack: state.currentTrack,
        playState: state.playState,
        playbackRate: state.playbackRate,
        setCurrentTrack,
        setPlaybackRate,
      }>
      children
    </Context.Provider>;
  };
};

let usePlayer = () => React.useContext(Context.t);
