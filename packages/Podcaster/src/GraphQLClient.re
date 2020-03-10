let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

module Http = {
  let make =
    ApolloLinks.createHttpLink(~uri="http://localhost:4000/graphql", ());
};

let client =
  ReasonApollo.createApolloClient(
    ~link=ApolloLinks.from([|Http.make|]),
    ~cache=inMemoryCache,
    (),
  );
