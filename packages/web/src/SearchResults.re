open ApolloHooks;

module SearchQuery = [%graphql
  {|
  query SearchQuery($query: String!) {
    search(query: $query) {
      artist
      id
      name
      url
    }
  }
|}
];

[@react.component]
let make = (~query, ~setQuery) => {
  let (podcastId, setPodcastId) = React.useState(() => None);
  let (result, _full) =
    useQuery(
      ~variables=
        SearchQuery.makeVariables(
          ~query=
            switch (query) {
            | Some(q) => q
            | None => ""
            },
          (),
        ),
      ~skip=Belt.Option.isNone(query),
      SearchQuery.definition,
    );

  <div>
    {switch (result) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       <ul>
         {data##search
          ->Belt.Array.map(search => {
              <li
                onClick={_ => {
                  setQuery(_ => None);
                  setPodcastId(_ => Some(search##id));
                }}
                key={search##id}>
                {React.string(search##name)}
              </li>
            })
          ->React.array}
       </ul>
     | NoData => React.null
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
    <Podcast podcastId setPodcastId />
  </div>;
};
