

//  testnav.appendChild(dropdownValue('sortDropdown',['Date Added','Last Modified','# images'],3,0))

function getDropdownMini(ulid,optionList,optionCt,prefix,initialChar)
{
  let U=UL.cloneNode(true)
  U.id=ulid
  U.className='dropsort'
  for (var i = 0; i < optionCt; ++i) {
    let L=LI.cloneNode(true)
    L.id = prefix[i] + String.fromCharCode(97 + i)
    L.className = 'noselect'
    L.textContent=optionList[i]
    U.appendChild(L)
  }
  return U
}

function getDropdownNav(ulid,optionList,optionCt,currentIdx,initialChar)
{
  /*
  <div class="dropdownSelector">
    <span id="sortMethodV" class="selClick crt">Average score</span>
    <ul id="sortDropdown" class="dropsort">
      <li id="Sd0" class="noselect active">Average score</li>
      <li id="Sd1" class="noselect">Median score</li>
      <li id="Sd2" class="noselect">Date created</li>
      <li id="Sd3" class="noselect">Date created</li>
    </ul>
  </div>
  */

  let DS=DIV.cloneNode(true)
  DS.className='dropdownSelector'
  
  // sort method
  let SM=SPN.cloneNode(true)
  SM.id='sortMethodV'
  SM.className='selClick crt'
  SM.nodeValue=optionList[currentIdx]

  let U=UL.cloneNode(true)
  U.id=ulid
  U.className='dropsort'
  for (var i = 0; i < optionCt; i+=1) {
    let L=LI.cloneNode(true)
    L.id = 'Sd' + String.fromCharCode(97 + i)
    L.className = 'noselect'
    L.nodeValue=optionList[i]
    U.appendChild(L)
  }
  U.children[currentIdx].className='noselect active'

  SM.nodeValue=optionList[currentIdx]

  DS.appendChild(SM)
  DS.appendChild(U)

  return DS
}
