import { ItunesAPI } from './datasource/itunes'
import { FeedAPI } from './datasource/feed'

export interface DataSources {
  feedAPI: FeedAPI
  itunesAPI: ItunesAPI
}

export interface PodcastContext {
  dataSources: DataSources
}

export interface ItunesResult {
  artistName: string
  artworkUrl600: string
  collectionId: string
  feedUrl: string
  genres: string[]
  trackName: string
}
