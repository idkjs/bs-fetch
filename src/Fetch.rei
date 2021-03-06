type body;

type bodyInit;

type headers;

type headersInit;

type response;

type request;

type requestInit;

/* external */
type arrayBuffer; /* TypedArray */

type blob; /* FileAPI */

type bufferSource; /* Web IDL, either an arrayBuffer or arrayBufferView */

type formData; /* XMLHttpRequest */

type readableStream; /* Streams */

type urlSearchParams; /* URL */

type requestMethod =
  | Get
  | Head
  | Post
  | Put
  | Delete
  | Connect
  | Options
  | Trace
  | Patch
  | Other(string);

type referrerPolicy =
  | None
  | NoReferrer
  | NoReferrerWhenDowngrade
  | SameOrigin
  | Origin
  | StrictOrigin
  | OriginWhenCrossOrigin
  | StrictOriginWhenCrossOrigin
  | UnsafeUrl;

type requestType =
  | None /* default? unknown? just empty string in spec */
  | Audio
  | Font
  | Image
  | Script
  | Style
  | Track
  | Video;

type requestDestination =
  | None /* default? unknown? just empty string in spec */
  | Document
  | Embed
  | Font
  | Image
  | Manifest
  | Media
  | Object
  | Report
  | Script
  | ServiceWorker
  | SharedWorker
  | Style
  | Worker
  | Xslt;

type requestMode =
  | Navigate
  | SameOrigin
  | NoCORS
  | CORS;

type requestCredentials =
  | Omit
  | SameOrigin
  | Include;

type requestCache =
  | Default
  | NoStore
  | Reload
  | NoCache
  | ForceCache
  | OnlyIfCached;

type requestRedirect =
  | Follow
  | Error
  | Manual;

module HeadersInit: {
  type t = headersInit;
  external make : Js.t({..}) => t = "%identity";
  external makeWithDict : Js.Dict.t(string) => t = "%identity";
  external makeWithArray : array((string, string)) => t = "%identity";
};

module Headers: {
  type t = headers;
  [@bs.new] external make : t = "Headers";
  [@bs.new] external makeWithInit : headersInit => t = "Headers";
  [@bs.send.pipe : t] external append : (string, string) => unit = "append";
  [@bs.send.pipe : t] external delete : string => unit = "delete" /* very experimental */; /* entries */
  [@bs.send.pipe : t] [@bs.return {null_to_opt: null_to_opt}]
  external get : string => option(string) = "get";
  [@bs.send.pipe : t] external has : string => bool = "has" /* very experimental */; /* keys */
  [@bs.send.pipe : t] external set : (string, string) => unit = "set" /* very experimental */; /* values */
};

module BodyInit: {
  type t = bodyInit;
  external make : string => t = "%identity";
  external makeWithBlob : blob => t = "%identity";
  external makeWithBufferSource : bufferSource => t = "%identity";
  external makeWithFormData : formData => t = "%identity";
  external makeWithUrlSearchParams : urlSearchParams => t = "%identity";
};

module Body: {
  type t = body;
  [@bs.get] external body : t => readableStream = "body";
  [@bs.get] external bodyUsed : t => bool = "bodyUsed";
  [@bs.send.pipe : t] external arrayBuffer : Js.Promise.t(arrayBuffer) = "arrayBuffer";
  [@bs.send.pipe : t] external blob : Js.Promise.t(blob) = "blob";
  [@bs.send.pipe : t] external formData : Js.Promise.t(formData) = "formData";
  [@bs.send.pipe : t] external json : Js.Promise.t(Js.Json.t) = "json";
  [@bs.send.pipe : t] external text : Js.Promise.t(string) = "text";
};

module RequestInit: {
  type t = requestInit;
  let make:
    (
      ~method_: requestMethod=?,
      ~headers: headersInit=?,
      ~body: bodyInit=?,
      ~referrer: string=?,
      ~referrerPolicy: referrerPolicy=?,
      ~mode: requestMode=?,
      ~credentials: requestCredentials=?,
      ~cache: requestCache=?,
      ~redirect: requestRedirect=?,
      ~integrity: string=?,
      ~keepalive: bool=?,
      unit
    ) =>
    t;
};

module Request: {
  type t = request;
  [@bs.new] external make : string => t = "Request";
  [@bs.new] external makeWithInit : (string, requestInit) => t = "Request";
  [@bs.new] external makeWithRequest : t => t = "Request";
  [@bs.new] external makeWithRequestInit : (t, requestInit) => t = "Request";

  [@bs.get] external url : t => string = "url";
  [@bs.get] external headers : t => headers = "headers";
  let type_: t => requestType;
  let destination: t => requestDestination;
  [@bs.get] external referrer : t => string = "referrer";
  let referrerPolicy: t => referrerPolicy;
  let mode: t => requestMode;
  let credentials: t => requestCredentials;
  let cache: t => requestCache;
  let redirect: t => requestRedirect;
  [@bs.get] external integrity : t => string = "integrity";
  [@bs.get] external keepalive : t => bool = "keepalive";
  /* Body Impl */
  [@bs.get] external body : t => readableStream = "body";
  [@bs.get] external bodyUsed : t => bool = "bodyUsed";
  [@bs.send.pipe : t] external arrayBuffer : Js.Promise.t(arrayBuffer) = "arrayBuffer";
  [@bs.send.pipe : t] external blob : Js.Promise.t(blob) = "blob";
  [@bs.send.pipe : t] external formData : Js.Promise.t(formData) = "formData";
  [@bs.send.pipe : t] external json : Js.Promise.t(Js.Json.t) = "json";
  [@bs.send.pipe : t] external text : Js.Promise.t(string) = "text";
};

module Response: {
  type t = response;
  [@bs.val] external error : unit => t = "error";
  [@bs.val] external redirect : string => t = "redirect";
  [@bs.val] external redirectWithStatus : (string, int /* enum-ish */) => t = "redirect";
  [@bs.get] external headers : t => headers = "headers";
  [@bs.get] external ok : t => bool = "ok";
  [@bs.get] external redirected : t => bool = "redirected";
  [@bs.get] external status : t => int = "status";
  [@bs.get] external statusText : t => string = "statusText";
  [@bs.get] external _type : t => string = "type";
  [@bs.get] external url : t => string = "url";
  [@bs.send.pipe : t] external clone : t = "clone";
  /* Body.Impl */
  [@bs.get] external body : t => readableStream = "body";
  [@bs.get] external bodyUsed : t => bool = "bodyUsed";
  [@bs.send.pipe : t] external arrayBuffer : Js.Promise.t(arrayBuffer) = "arrayBuffer";
  [@bs.send.pipe : t] external blob : Js.Promise.t(blob) = "blob";
  [@bs.send.pipe : t] external formData : Js.Promise.t(formData) = "formData";
  [@bs.send.pipe : t] external json : Js.Promise.t(Js.Json.t) = "json";
  [@bs.send.pipe : t] external text : Js.Promise.t(string) = "text";
};

[@bs.val] external fetch : string => Js.Promise.t(response) = "fetch";

[@bs.val] external fetchWithInit : (string, requestInit) => Js.Promise.t(response) = "fetch";

[@bs.val] external fetchWithRequest : request => Js.Promise.t(response) = "fetch";

[@bs.val]
external fetchWithRequestInit : (request, requestInit) => Js.Promise.t(response) = "fetch";
