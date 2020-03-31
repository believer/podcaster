ReactDOMRe.renderToElementWithId(
  <ApolloHooks.Provider client=GraphQL.client>
    <Player.Provider> <App /> </Player.Provider>
  </ApolloHooks.Provider>,
  "root",
);
