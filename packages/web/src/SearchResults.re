open ApolloHooks;

module SearchQuery = [%graphql
  {|
  query SearchMutation($query: String!) {
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
let make = (~query) => {
  let (result, _full) =
    useQuery(
      ~variables=SearchQuery.makeVariables(~query, ()),
      ~skip=Js.String.length(query) === 0,
      SearchQuery.definition,
    );

  <div>
    {switch (result) {
     | Loading => <p> {React.string("Loading...")} </p>
     | Data(data) =>
       <ul>
         {data##search
          ->Belt.Array.map(search => {
              <li key={search##id}> {React.string(search##name)} </li>
            })
          ->React.array}
       </ul>
     | NoData => React.null
     | Error(_) => <p> {React.string("Get off my lawn!")} </p>
     }}
  </div>;
};
