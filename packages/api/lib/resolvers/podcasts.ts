import { gql } from 'apollo-server-core'
import { Resolvers } from '../__generated__/graphql'

export const typeDefs = gql`
  type PodcastEpisode {
    date: String!
    description: String!
    duration: String!
    id: ID!
    title: String!
    url: String!
  }

  type Podcast {
    description: String!
    episodes: [PodcastEpisode!]!
    link: String
    image: String
    title: String!
  }

  extend type Query {
    latestEpisode(id: ID!): PodcastEpisode!
    podcast(limit: Int = 10, id: ID!): Podcast
  }
`

export const resolvers: Resolvers = {
  Query: {
    latestEpisode: async (_, { id }, { dataSources }) => {
      const data = await dataSources.itunesAPI.lookup(id)
      const feed = await dataSources.feedAPI.getFeed(data.url)

      return feed.episodes[0]
    },

    podcast: async (_, { id, limit }, { dataSources }) => {
      const data = await dataSources.itunesAPI.lookup(id)
      const feed = await dataSources.feedAPI.getFeed(data.url)

      return {
        ...feed,
        episodes: feed.episodes.slice(0, limit),
      }
    },
  },
}
