// https://developer.chrome.com/en/articles/webtransport/


const url = 'https://example.com:4999/foo/bar';
const transport = new WebTransport(url);

// Optionally, set up functions to respond to
// the connection closing:
transport.closed.then(() => {
  console.log(`The HTTP/3 connection to ${url} closed gracefully.`);
}).catch((error) => {
  console.error(`The HTTP/3 connection to ${url} closed due to ${error}.`);
});

// Once .ready fulfills, the connection can be used.
await transport.ready;


// Send two datagrams to the server.
const writer = transport.datagrams.writable.getWriter();
const data1 = new Uint8Array([65, 66, 67]);
const data2 = new Uint8Array([68, 69, 70]);
writer.write(data1);
writer.write(data2);

// Read datagrams from the server.
const reader = transport.datagrams.readable.getReader();
while (true) {
  const {value, done} = await reader.read();
  if (done) {
    break;
  }
  // value is a Uint8Array.
  console.log(value);
}
