open ApolloHooks;

module PodcastQuery = [%graphql
  {|
query PodcastQuery($id: ID!) {
  podcast(id: $id) {
    image
    title
    episodes {
      description
      title
      id
      url
    }
  }
}
|}
];

[@react.component]
let make = (~podcastId as id, ~setPodcastId) => {
  let {setCurrentTrack}: Player.Context.t = Player.usePlayer();
  let (result, _full) =
    useQuery(
      ~variables=
        PodcastQuery.makeVariables(
          ~id=
            switch (id) {
            | Some(id) => id
            | None => ""
            },
          (),
        ),
      ~skip=Belt.Option.isNone(id),
      PodcastQuery.definition,
    );

  <div>
    {switch (result) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       switch (data##podcast) {
       | Some(podcast) =>
         <div>
           {React.string(podcast##title)}
           <ul>
             {podcast##episodes
              ->Belt.Array.map(episode => {
                  <li
                    onClick={_ => {
                      setCurrentTrack(episode, podcast##image);
                      setPodcastId(_ => None);
                    }}
                    key={episode##id}>
                    {React.string(episode##title)}
                  </li>
                })
              ->React.array}
           </ul>
         </div>
       | None => React.string("No podcast")
       }
     | NoData => React.null
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
  </div>;
};
