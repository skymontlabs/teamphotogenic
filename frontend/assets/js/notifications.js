
function addNotifications() {
  /*
    <li class="notifItem">
      <a class="y pl f13 lh20 w5" href="/tests.html">
        <img src="img/square.jpg" alt="">
        <span>Your test has finished with 45 votes.</span>
      </a>
      <span class="delete-elem"></span>
    </li>
  */
  const del = document.createElement('span')
  del.className='delete-elem'

  for (var i = 0; i < 10; ++i) {
    const lii = document.createElement('li')
    const link = document.createElement('a')
    const img = document.createElement('img')
    const txt = document.createElement('span')

    lii.className='notifItem'
    link.className='y pl f13 lh20 w5'
    link.href='/profile'
    img.src='img/square.jpg'
    txt.firstChild.nodeValue='Your '

    link.appendChild(img)
    link.appendChild(txt)
    lii.appendChild(link)
    lii.appendChild(del.cloneNode(true))

    nla.appendChild(lii)
  }
}
//addNotifications()
