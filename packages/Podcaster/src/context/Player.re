module Episode = {
  type t = {
    artwork: option(string),
    duration: string,
    url: string,
    podcast: string,
    title: string,
  };

  let make = (~episode, ~podcast) =>
    Some({
      artwork: podcast##image,
      duration: episode##duration,
      url: episode##url,
      podcast: podcast##title,
      title: episode##title,
    });
};

type t = {
  currentEpisode: option(Episode.t),
  setEpisode: option(Episode.t) => unit,
};

type state = {episode: option(Episode.t)};

module Context = {
  include ReactContext.Make({
    type context = t;

    let defaultValue = {currentEpisode: None, setEpisode: _ => ()};
  });
};

type action =
  | SetCurrentEpisode(option(Episode.t));

module Provider = {
  [@react.component]
  let make = (~children) => {
    let (state, dispatch) =
      React.useReducer(
        (_state, action) => {
          switch (action) {
          | SetCurrentEpisode(episode) => {episode: episode}
          }
        },
        {episode: None},
      );

    let setEpisode =
      React.useCallback(episode => dispatch(SetCurrentEpisode(episode)));

    let value =
      React.useMemo(_ => {currentEpisode: state.episode, setEpisode});

    <Context.Provider value> children </Context.Provider>;
  };
};

let usePlayer = () => React.useContext(Context.t);
