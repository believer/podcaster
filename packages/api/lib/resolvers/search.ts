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
    search(query: String!, limit: Int = 10): [SearchResult!]!
  }
`

export const resolvers: Resolvers = {
  Query: {
    search: async (_, args, { dataSources }) =>
      dataSources.itunesAPI.search(args),
  },
}
