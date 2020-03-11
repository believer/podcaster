import { GraphQLResolveInfo, GraphQLScalarType, GraphQLScalarTypeConfig } from 'graphql';
import { PodcastContext } from '../types';
export type Maybe<T> = T | null;
export type RequireFields<T, K extends keyof T> = { [X in Exclude<keyof T, K>]?: T[X] } & { [P in K]-?: NonNullable<T[P]> };
/** All built-in and custom scalars, mapped to their actual values */
export type Scalars = {
  ID: string,
  String: string,
  Boolean: boolean,
  Int: number,
  Float: number,
  /** The `Upload` scalar type represents a file upload. */
  Upload: any,
};


export enum CacheControlScope {
  Public = 'PUBLIC',
  Private = 'PRIVATE'
}

export type Mutation = {
   __typename?: 'Mutation',
  _empty?: Maybe<Scalars['String']>,
  search: Array<SearchResult>,
};


export type MutationSearchArgs = {
  input: SearchInput
};

export type Podcast = {
   __typename?: 'Podcast',
  description: Scalars['String'],
  episodes: Array<PodcastEpisode>,
  link?: Maybe<Scalars['String']>,
  image?: Maybe<Scalars['String']>,
  title: Scalars['String'],
};

export type PodcastEpisode = {
   __typename?: 'PodcastEpisode',
  date: Scalars['String'],
  description: Scalars['String'],
  duration: Scalars['String'],
  id: Scalars['ID'],
  title: Scalars['String'],
  url: Scalars['String'],
};

export type Query = {
   __typename?: 'Query',
  _empty?: Maybe<Scalars['String']>,
  latestEpisode: PodcastEpisode,
  podcast?: Maybe<Podcast>,
};


export type QueryLatestEpisodeArgs = {
  id: Scalars['ID']
};


export type QueryPodcastArgs = {
  limit?: Maybe<Scalars['Int']>,
  id: Scalars['ID']
};

export type SearchInput = {
  limit?: Maybe<Scalars['Int']>,
  query: Scalars['String'],
};

export type SearchResult = {
   __typename?: 'SearchResult',
  artist: Scalars['String'],
  artwork: Scalars['String'],
  id: Scalars['ID'],
  genres: Array<Maybe<Scalars['String']>>,
  name: Scalars['String'],
  url: Scalars['String'],
};




export type ResolverTypeWrapper<T> = Promise<T> | T;

export type ResolverFn<TResult, TParent, TContext, TArgs> = (
  parent: TParent,
  args: TArgs,
  context: TContext,
  info: GraphQLResolveInfo
) => Promise<TResult> | TResult;


export type StitchingResolver<TResult, TParent, TContext, TArgs> = {
  fragment: string;
  resolve: ResolverFn<TResult, TParent, TContext, TArgs>;
};

export type Resolver<TResult, TParent = {}, TContext = {}, TArgs = {}> =
  | ResolverFn<TResult, TParent, TContext, TArgs>
  | StitchingResolver<TResult, TParent, TContext, TArgs>;

export type SubscriptionSubscribeFn<TResult, TParent, TContext, TArgs> = (
  parent: TParent,
  args: TArgs,
  context: TContext,
  info: GraphQLResolveInfo
) => AsyncIterator<TResult> | Promise<AsyncIterator<TResult>>;

export type SubscriptionResolveFn<TResult, TParent, TContext, TArgs> = (
  parent: TParent,
  args: TArgs,
  context: TContext,
  info: GraphQLResolveInfo
) => TResult | Promise<TResult>;

export interface SubscriptionSubscriberObject<TResult, TKey extends string, TParent, TContext, TArgs> {
  subscribe: SubscriptionSubscribeFn<{ [key in TKey]: TResult }, TParent, TContext, TArgs>;
  resolve?: SubscriptionResolveFn<TResult, { [key in TKey]: TResult }, TContext, TArgs>;
}

export interface SubscriptionResolverObject<TResult, TParent, TContext, TArgs> {
  subscribe: SubscriptionSubscribeFn<any, TParent, TContext, TArgs>;
  resolve: SubscriptionResolveFn<TResult, any, TContext, TArgs>;
}

export type SubscriptionObject<TResult, TKey extends string, TParent, TContext, TArgs> =
  | SubscriptionSubscriberObject<TResult, TKey, TParent, TContext, TArgs>
  | SubscriptionResolverObject<TResult, TParent, TContext, TArgs>;

export type SubscriptionResolver<TResult, TKey extends string, TParent = {}, TContext = {}, TArgs = {}> =
  | ((...args: any[]) => SubscriptionObject<TResult, TKey, TParent, TContext, TArgs>)
  | SubscriptionObject<TResult, TKey, TParent, TContext, TArgs>;

export type TypeResolveFn<TTypes, TParent = {}, TContext = {}> = (
  parent: TParent,
  context: TContext,
  info: GraphQLResolveInfo
) => Maybe<TTypes>;

export type NextResolverFn<T> = () => Promise<T>;

export type DirectiveResolverFn<TResult = {}, TParent = {}, TContext = {}, TArgs = {}> = (
  next: NextResolverFn<TResult>,
  parent: TParent,
  args: TArgs,
  context: TContext,
  info: GraphQLResolveInfo
) => TResult | Promise<TResult>;

/** Mapping between all available schema types and the resolvers types */
export type ResolversTypes = {
  Query: ResolverTypeWrapper<{}>,
  String: ResolverTypeWrapper<Scalars['String']>,
  ID: ResolverTypeWrapper<Scalars['ID']>,
  PodcastEpisode: ResolverTypeWrapper<PodcastEpisode>,
  Int: ResolverTypeWrapper<Scalars['Int']>,
  Podcast: ResolverTypeWrapper<Podcast>,
  Mutation: ResolverTypeWrapper<{}>,
  SearchInput: SearchInput,
  SearchResult: ResolverTypeWrapper<SearchResult>,
  Boolean: ResolverTypeWrapper<Scalars['Boolean']>,
  CacheControlScope: CacheControlScope,
  Upload: ResolverTypeWrapper<Scalars['Upload']>,
};

/** Mapping between all available schema types and the resolvers parents */
export type ResolversParentTypes = {
  Query: {},
  String: Scalars['String'],
  ID: Scalars['ID'],
  PodcastEpisode: PodcastEpisode,
  Int: Scalars['Int'],
  Podcast: Podcast,
  Mutation: {},
  SearchInput: SearchInput,
  SearchResult: SearchResult,
  Boolean: Scalars['Boolean'],
  CacheControlScope: CacheControlScope,
  Upload: Scalars['Upload'],
};

export type CacheControlDirectiveResolver<Result, Parent, ContextType = PodcastContext, Args = {   maxAge?: Maybe<Maybe<Scalars['Int']>>,
  scope?: Maybe<Maybe<CacheControlScope>> }> = DirectiveResolverFn<Result, Parent, ContextType, Args>;

export type MutationResolvers<ContextType = PodcastContext, ParentType extends ResolversParentTypes['Mutation'] = ResolversParentTypes['Mutation']> = {
  _empty?: Resolver<Maybe<ResolversTypes['String']>, ParentType, ContextType>,
  search?: Resolver<Array<ResolversTypes['SearchResult']>, ParentType, ContextType, RequireFields<MutationSearchArgs, 'input'>>,
};

export type PodcastResolvers<ContextType = PodcastContext, ParentType extends ResolversParentTypes['Podcast'] = ResolversParentTypes['Podcast']> = {
  description?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  episodes?: Resolver<Array<ResolversTypes['PodcastEpisode']>, ParentType, ContextType>,
  link?: Resolver<Maybe<ResolversTypes['String']>, ParentType, ContextType>,
  image?: Resolver<Maybe<ResolversTypes['String']>, ParentType, ContextType>,
  title?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
};

export type PodcastEpisodeResolvers<ContextType = PodcastContext, ParentType extends ResolversParentTypes['PodcastEpisode'] = ResolversParentTypes['PodcastEpisode']> = {
  date?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  description?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  duration?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  id?: Resolver<ResolversTypes['ID'], ParentType, ContextType>,
  title?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  url?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
};

export type QueryResolvers<ContextType = PodcastContext, ParentType extends ResolversParentTypes['Query'] = ResolversParentTypes['Query']> = {
  _empty?: Resolver<Maybe<ResolversTypes['String']>, ParentType, ContextType>,
  latestEpisode?: Resolver<ResolversTypes['PodcastEpisode'], ParentType, ContextType, RequireFields<QueryLatestEpisodeArgs, 'id'>>,
  podcast?: Resolver<Maybe<ResolversTypes['Podcast']>, ParentType, ContextType, RequireFields<QueryPodcastArgs, 'limit' | 'id'>>,
};

export type SearchResultResolvers<ContextType = PodcastContext, ParentType extends ResolversParentTypes['SearchResult'] = ResolversParentTypes['SearchResult']> = {
  artist?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  artwork?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  id?: Resolver<ResolversTypes['ID'], ParentType, ContextType>,
  genres?: Resolver<Array<Maybe<ResolversTypes['String']>>, ParentType, ContextType>,
  name?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
  url?: Resolver<ResolversTypes['String'], ParentType, ContextType>,
};

export interface UploadScalarConfig extends GraphQLScalarTypeConfig<ResolversTypes['Upload'], any> {
  name: 'Upload'
}

export type Resolvers<ContextType = PodcastContext> = {
  Mutation?: MutationResolvers<ContextType>,
  Podcast?: PodcastResolvers<ContextType>,
  PodcastEpisode?: PodcastEpisodeResolvers<ContextType>,
  Query?: QueryResolvers<ContextType>,
  SearchResult?: SearchResultResolvers<ContextType>,
  Upload?: GraphQLScalarType,
};


/**
 * @deprecated
 * Use "Resolvers" root object instead. If you wish to get "IResolvers", add "typesPrefix: I" to your config.
*/
export type IResolvers<ContextType = PodcastContext> = Resolvers<ContextType>;
export type DirectiveResolvers<ContextType = PodcastContext> = {
  cacheControl?: CacheControlDirectiveResolver<any, any, ContextType>,
};


/**
* @deprecated
* Use "DirectiveResolvers" root object instead. If you wish to get "IDirectiveResolvers", add "typesPrefix: I" to your config.
*/
export type IDirectiveResolvers<ContextType = PodcastContext> = DirectiveResolvers<ContextType>;