import { gql } from 'apollo-server-core'
import { Resolvers } from '../__generated__/graphql'

export const typeDefs = gql`
  type SearchResult {
    artist: String!
    artwork: String!
    id: ID!
    genres: [String]!
    name: String!
    url: String!
  }

  input SearchInput {
    limit: Int = 10
    query: String!
  }

  extend type Mutation {
    search(input: SearchInput!): [SearchResult!]!
  }
`

export const resolvers: Resolvers = {
  Mutation: {
    search: async (_, { input }, { dataSources }) =>
      dataSources.itunesAPI.search(input),
  },
}
