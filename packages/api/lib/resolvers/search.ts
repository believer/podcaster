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

  extend type Query {
    search(limit: Int = 10, query: String!): [SearchResult!]!
  }
`

export const resolvers: Resolvers = {
  Query: {
    search: async (_, { limit, query }, { dataSources }) =>
      dataSources.itunesAPI.search({ limit, query }),
  },
}
