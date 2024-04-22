function filterStatus()
{
  let Bn = BTN.cloneNode(true)
  Bn.id='Bv0'
  Bn.className='btn'

  let Sx = SPN.cloneNode(true)
  Sx.id='Bw0'
  Sx.className='F12 ST'
  Sx.textContent='All'

  let Zx = H4.cloneNode(true)
  Zx.id='Bx0'
  Zx.textContent='14'
  Bn.appendChild(Sx)
  Bn.appendChild(Zx)

  let b1 = Bn.cloneNode(true)
  b1.id='Bv1'
  b1.children[0].id='Bw1'
  b1.children[0].textContent='Running'
  b1.children[1].id='Bx1'
  b1.children[1].textContent='1'
  let b2 = Bn.cloneNode(true)
  b2.id='Bv2'
  b2.children[0].id='Bw2'
  b2.children[0].textContent='Paused'
  b2.children[1].id='Bx2'
  b2.children[1].textContent='12'
  let b3 = Bn.cloneNode(true)
  b3.id='Bv3'
  b3.children[0].id='Bw3'
  b3.children[0].textContent='Finished'
  b3.children[1].id='Bx3'
  b3.children[1].textContent='1'
  Bn.className='btn A'


  let Pr = DIV.cloneNode(true)
  Pr.id='imagesetFilterbar'
  Pr.appendChild(Bn)
  Pr.appendChild(b1)
  Pr.appendChild(b2)
  Pr.appendChild(b3)

  //Ta.children[0].appendChild(Pr)
  return Pr
}

function getTimeDistanceToTodayOptimized(unixTimestamp)
{
    const givenDate = new Date(unixTimestamp * 1000);
    const today = new Date();

    // Calculate the total difference in days first (most likely scenario)
    const differenceInDays = Math.floor((today - givenDate) / (86400000));

    if (differenceInDays >= 365) {
        const years = Math.floor(differenceInDays / 365);
        return `${years}y`;
    } else if (differenceInDays >= 30) {
        const months = Math.floor(differenceInDays / 30); // A rough approximation
        return `${months}m`;
    } else if (differenceInDays >= 1) {
        return `${differenceInDays}d`;
    } else {
        // If less than a day, calculate hours, then minutes, then seconds
        const differenceInHours = Math.floor((today - givenDate) / (3600000));
        if (differenceInHours >= 1) {
            return `${differenceInHours}h`;
        } else {
            const differenceInMinutes = Math.floor((today - givenDate) / (60000));
            if (differenceInMinutes >= 1) {
                return `${differenceInMinutes}min`;
            } else {
                const differenceInSeconds = Math.floor((today - givenDate) / 1000);
                return `${differenceInSeconds}sec`;
            }
        }
    }
}



function taskData(id, title, imgs, age)
{
  const taskItem = DIV.cloneNode(true)
  taskItem.className = 'taskItem'

  const imgWrap = DIV.cloneNode(true)
  imgWrap.className = 'imgWrp'
  const imgMat = AX.cloneNode(true)
  imgMat.style.backgroundImage = `url("img/${imgs[0]}")`
  imgMat.style.backgroundSize = 'cover'
  imgMat.href = '/imageID'
  for (var i = 1; i < 4; ++i) {
    const imgClone = imgMat.cloneNode(true)
    imgClone.style.backgroundImage = `url("img/${imgs[i]}")`
    imgClone.style.height = '130px'
    imgWrap.appendChild(imgClone)
  }
  imgMat.className = 'fillImg'

  const txtWrap = DIV.cloneNode(true)
  txtWrap.className = 'y rel'
  const tdv = document.createElement('a')
  tdv.href='/taskID'
  tdv.textContent = title
  const imgCt = SPN.cloneNode(true)
  imgCt.className = 'dtpt'
  imgCt.textContent = '13 images'
  const time = document.createElement('time')
  time.textContent = getTimeDistanceToTodayOptimized(age)
  const dtv = HMB.cloneNode(true)
  dtv.id = 'Y'+ id

  let mod = getDropdownMini('Z'+ id,['Delete','Pause','Resume'],3,['Q','K','J'],'U')
  CTRLV.iDropdownLUT['Y'+ id] = mod
  console.log(mod)


  txtWrap.appendChild(tdv)
  txtWrap.appendChild(imgCt)
  txtWrap.appendChild(time)
  txtWrap.appendChild(dtv)
  txtWrap.appendChild(mod)


  taskItem.appendChild(imgMat)
  taskItem.appendChild(imgWrap)
  taskItem.appendChild(txtWrap)

  return taskItem
}


function dropdownValue(ulid,chld,chldct,acv,baseval)
{
  let DS=DIV.cloneNode(true)
  DS.className='dropdownSelector'
  
  let SM=SPN.cloneNode(true)
  SM.id='sortMethodV'
  SM.className='selClick crt'
  SM.textContent=chld[acv]

  let U=UL.cloneNode(true)
  U.id=ulid
  U.className='dropsort'
  for (var i = 0; i < chldct; i+=1) {
    let L=LI.cloneNode(true)
    L.id = 'Sd' + String.fromCharCode(baseval + i)
    L.className = 'noselect'
    L.textContent=chld[i]
    U.appendChild(L)
  }
  U.children[acv].className='noselect active'

  SM.textContent=chld[acv]

  DS.appendChild(SM)
  DS.appendChild(U)

  return DS
}

function getTestNav()
{
  var TsT=H2.cloneNode(true)
  TsT.id='Fa'
  TsT.textContent='Tests'

  var testnav=DIV.cloneNode(true) 
  testnav.className='wrapsort y z rel BB'

  testnav.appendChild(TsT)
  testnav.appendChild(dropdownValue('sortDropdown',IMAGESET_SORT_FUNCTIONS,3,0,48))

  return testnav
}

function getAllImagesets(imagesetCt)
{
  Mn.id='Ta'

  Mn.children[0].appendChild(getTestNav())
  Mn.children[0].appendChild(filterStatus())
  
  var Tls=DIV.cloneNode(true)
  Tls.id='TLS'
  Tls.className='G'

  let ict = DATAV.iImagesetList.length
  for (let i = 0; i < ict; ++i) {
    let ims = DATAV.iImagesetList[i]
    Tls.appendChild(taskData(ims[0], ims[2], ims[1], ims[4]))
  }

  Mn.children[0].appendChild(Tls)
}


function getAllTests() {
  getAllImagesets(1)
}





function imageIndiv(imgSrc, scorePt, votesCt) {
  const imgItem = DIV.cloneNode(true)
  imgItem.className = 'taskItem rel'

  const imgWrap = AX.cloneNode(true)
  imgWrap.className = ''
  imgWrap.href = '/imageID'
  const imgMat = document.createElement('img')
  imgMat.src = `img/${imgSrc}`
  imgMat.alt = 'Sample image'
  imgWrap.appendChild(imgMat)


  const mtaWrap = DIV.cloneNode(true)
  mtaWrap.className = 'W D imgData abs y z'

  const score = SPN.cloneNode(true)
  
  const ctWrap = DIV.cloneNode(true)
  const comCt = score.cloneNode(true)
  comCt.className = 'acomm'
  score.className = 'ascore'
  score.textContent = scorePt
  ctWrap.className = 'mla'
  comCt.textContent = `${votesCt} votes`

  ctWrap.appendChild(comCt)
  mtaWrap.appendChild(score)
  mtaWrap.appendChild(ctWrap)

  imgItem.appendChild(imgWrap)
  imgItem.appendChild(mtaWrap)

  return imgItem
}


function getPaired() {
  // Create the outermost div
  //let divXa=DIV.cloneNode(true);
  Mn.id='Xa';

  // Create the child div with class 'x'
  let divX=Mn.children[0]

  // Create the div with id 'RSa'
  let divRSa=DIV.cloneNode(true)
  divRSa.id='RSa';

  // Create the first inner div with id 'IWa' and class 'PI'
  let divIWa=DIV.cloneNode(true)
  divIWa.id='IWa';
  divIWa.className='PI';

  // Create the img inside 'IWa'
  let imgIMa=document.createElement('img');
  imgIMa.id='IMa';
  imgIMa.src='img/laurie.jpg';

  // Append imgIMa to divIWa
  divIWa.appendChild(imgIMa);

  // Create the second inner div with id 'IWb' and class 'PI'
  let divIWb = DIV.cloneNode(true)
  divIWb.id = 'IWb';
  divIWb.className = 'PI';

  // Create the img inside 'IWb'
  let imgIMb = document.createElement('img');
  imgIMb.id = 'IMb';
  imgIMb.src = 'img/lake.jpg';

  // Append imgIMb to divIWb
  divIWb.appendChild(imgIMb);

  // Append divIWa and divIWb to divRSa
  divRSa.appendChild(divIWa);
  divRSa.appendChild(divIWb);

  // Append divRSa to divX
  divX.appendChild(divRSa);

}


function cr8_dt()
{
  let DT = BTN.cloneNode(true)
  DT.className = 'dots btn L16'
  let D0 = SPN.cloneNode(true)
  D0.className = 'd0'
  let D1 = SPN.cloneNode(true)
  D1.className = 'd1'
  let D2 = SPN.cloneNode(true)
  D2.className = 'd2'

  DT.appendChild(D0)
  DT.appendChild(D1)
  DT.appendChild(D2)

  return DT
}

let DZ = cr8_dt()

function formatTime(date) {
    const hours = date.getHours().toString().padStart(2, '0');
    const minutes = date.getMinutes().toString().padStart(2, '0');
    return `${hours}:${minutes}`;
}

function formatDate(date) {
    const dateString = date.toLocaleDateString();
    const timeString = formatTime(date);
    return `${dateString}, ${timeString}`;
}

// Example usage:


function date2str(unix_timestamp) {
  // Create a new Date object from the Unix timestamp.
  var currentDate = new Date(unix_timestamp * 1000);


const formattedDate = formatDate(currentDate);
console.log();
return formattedDate


}


function s()
{



  const masonrySVG = document.createElementNS("http://www.w3.org/2000/svg", "svg");
  masonrySVG.setAttribute("width", "24");
  masonrySVG.setAttribute("height", "24");
  masonrySVG.setAttribute("viewBox", "0 0 24 24");



  const hotdogSVG = document.createElementNS("http://www.w3.org/2000/svg", "svg");
  hotdogSVG.setAttribute("width", "24");
  hotdogSVG.setAttribute("height", "24");
  hotdogSVG.setAttribute("viewBox", "0 0 24 24");

  const path3 = document.createElementNS("http://www.w3.org/2000/svg", "path");
  path3.setAttribute("d", "M4 7v10h16V7H4zm2 2h12v6H6V9z");

  hotdogSVG.appendChild(path3);
}

function generateImagesetMetadata(title, imageId, statusInt, imageCt, voteCt, unix)
{
  // First inner div with classes 'y' and 'z'
  let spanRQ=SPN.cloneNode(true);
  spanRQ.id='RQ';
  spanRQ.textContent='Rating Test';

  let spanRQ2=SPN.cloneNode(true);
  spanRQ2.id='RQ2';
  spanRQ2.textContent='ts_' + (imageId);

  let divYz=DYZ.cloneNode(true);
  divYz.appendChild(spanRQ);
  divYz.appendChild(spanRQ2);

  let spanBW=SPN.cloneNode(true)
  spanBW.className = 'BW';
  spanBW.textContent = [statusInt];//'Running'; // STATUS[]

  let imagesetTitle = H2.cloneNode(true);
  imagesetTitle.id = 'imagesetTitle'
  imagesetTitle.textContent=title; // title
  imagesetTitle.appendChild(spanBW);

  // hamburger
  let hamburgerCtrl = HMB.cloneNode(true)
  hamburgerCtrl.id='dtz'
  hamburgerCtrl.className='dots btn L16'

  let dropdownPanel = UL.cloneNode(true)
  dropdownPanel.id = 'bblDropdown';
  dropdownPanel.className = 'dropsort';

  ////
  const cmds = ['Restart test','Resume test','Pause test','Edit test','Delete test']
  for (let i = 0; i < 5; ++i) {
    let li = LI.cloneNode(true)
    let span = SPN.cloneNode(true)
    span.id = `edit${i}`;
    span.textContent = cmds[i];
    li.appendChild(span);
    dropdownPanel.appendChild(li);
  }
  ////

  let divRelYBB=DIV.cloneNode(true);
  divRelYBB.className='rel y BB';
  divRelYBB.appendChild(imagesetTitle)
  divRelYBB.appendChild(hamburgerCtrl)
  divRelYBB.appendChild(dropdownPanel)

  let ctrlBar=DIV.cloneNode(true)
  ctrlBar.className = 'y z t16';
  let stats=DIV.cloneNode(true)
  stats.className = 'y';
  let viewToggler=DIV.cloneNode(true)
  viewToggler.className = 'y';


  const deet = ['total images','total votes','created']
  const clsn = ['BY r16','BY L16 r16','L16']
  const txtc = [imageCt,voteCt,date2str(unix)]
  for (let i = 0; i < 3; ++i) {
    let div = DIV.cloneNode(true)
    div.className = clsn[i]
    
    let spanST = SPN.cloneNode(true)
    spanST.className = 'F12 ST';
    spanST.textContent = deet[i];
    
    let spanBl = SPN.cloneNode(true)
    spanBl.className = 'bl';
    spanBl.textContent = txtc[i]
    
    div.appendChild(spanST);
    div.appendChild(spanBl);
    stats.appendChild(div);
    //viewToggler.appendChild()
  }


  const squareGridSVG = document.createElementNS("http://www.w3.org/2000/svg", "svg");
  squareGridSVG.setAttribute("width", "24");
  squareGridSVG.setAttribute("height", "24");
  squareGridSVG.setAttribute("viewBox", "0 0 24 24");

  const path = document.createElementNS("http://www.w3.org/2000/svg", "path");
  path.setAttribute("d", "M4 5v14h14V5H4zm2 2h10v10H6V7zm2 2v2h2V9H8zm4 0v2h2V9h-2zm-4 4v2h2v-2H8zm4 0v2h2v-2h-2zm-4 4v2h2v-2H8zm4 0v2h2v-2h-2z");
  squareGridSVG.appendChild(path);

  const masonrySVG = squareGridSVG.cloneNode(true)
  masonrySVG.children[0].setAttribute("d", "M4 5v14h14V5H4zm2 2h10v4H6V7zm0 6h4v6H6v-6zm6 0h6v6h-6v-6zm0 8h6v2h-6v-2z");

  const hotdogSVG = squareGridSVG.cloneNode(true)
  hotdogSVG.children[0].setAttribute("d", "M4 7v10h16V7H4zm2 2h12v6H6V9z");

  viewToggler.appendChild(squareGridSVG)
  viewToggler.appendChild(masonrySVG)
  viewToggler.appendChild(hotdogSVG)

  ctrlBar.appendChild(stats)
  ctrlBar.appendChild(viewToggler)

  let spanFontSize = SPN.cloneNode(true)
  spanFontSize.style.fontSize = '11px';

  let divTMta=DIV.cloneNode(true)
  divTMta.id='TMta';
  divTMta.appendChild(divYz);
  divTMta.appendChild(divRelYBB);
  divTMta.appendChild(ctrlBar);
  divTMta.appendChild(spanFontSize);

  DOMSHORTCUTS.imagesetTitle = imagesetTitle

  return divTMta
}


function getRandomColor() {
    const letters = '0123456789ABCDEF';
    let color = '#';
    for (let i = 0; i < 6; i++) {
        color += letters[Math.floor(Math.random() * 16)];
    }
    return color;
}


function generateRowsz() {
  let dataArray = [
    {
      imageUrl: '/img/square.jpg',
      votes: [4,5,9,11,17], // Percentages
      totalVotes: 100,
      score: 0.4
    },
    {
      imageUrl: '/img/laurie.jpg',
      votes: [11,5,3,2,17], // Percentages
      totalVotes: 100,
      score: 0.4
    },
    {
      imageUrl: '/img/laurie.jpg',
      votes: [9,5,2,20,17], // Percentages
      totalVotes: 100,
      score: 0.4
    },
    {
      imageUrl: '/img/laurie.jpg',
      votes: [4,8,9,11,22], // Percentages
      totalVotes: 100,
      score: 0.4
    },
  ];
    let colors = ['#A0B8FF', '#89A3FF', '#5984FF', '#4E62E3', '#293556']
    let options = ['distributions', 'adj. distributions', 'intervals']

    let parentStatTypes = DIV.cloneNode(true)
    for (let i = 0; i < 3; ++i) {
      let z = SPN.cloneNode(true)
      z.textContent = options[i]
      parentStatTypes.appendChild(z)
    }


    let container = Mn.children[0]

    container.appendChild(parentStatTypes)




    dataArray.forEach((data, index) => {
      const row = document.createElement('div');
      row.id = `Q${index}`;
      row.className = `imgrw`;

      // Image
      const img = document.createElement('img');
      img.src = data.imageUrl;
      img.className = 'imgStat'

      // Bar chart (Likert scale representation)
      const chartWrap = document.createElement('div');
      const chart = document.createElement('div');
      chartWrap.className = 'chartWrap'
      chart.className = 'chartParent'

      let sum = 0
      for (let i = 0; i < 5; ++i) {
        sum += data.votes[i]
      }

      for (let i = 0; i < 5; ++i) {
        const v = data.votes[i]
        const bar = document.createElement('div');
        bar.style.width = `${v/sum * 50}%`;
        bar.style.height = '40px';
        bar.style.backgroundColor = colors[i]
        chart.appendChild(bar);
      }

      let sub = (data.votes[0] / sum) * 50
      sub += (data.votes[1] / sum) * 50
      sub += (data.votes[2] / sum) * 25

      chart.style.left = `calc(${50 - sub}%)`;

      const rating = document.createElement('div');
      rating.innerText = `${data.score}`;
      rating.style.flexShrink = '0';
      rating.style.marginRight = '20px';

      const voteCount = document.createElement('div');
      voteCount.innerText = `${data.totalVotes} votes`;
      voteCount.style.flexShrink = '0';

      chartWrap.appendChild(chart)
      row.appendChild(img);
      row.appendChild(chartWrap);
      row.appendChild(rating);
      row.appendChild(voteCount);

      container.appendChild(row);
   });

}




function getTestID()
{
  Mn.id='Ta';
  Mn.className='oh';
  Mn.children[0].appendChild( generateImagesetMetadata('TAYLOR', 4, 2, 2, 200, 102040))
  var Tls=DIV.cloneNode(true)
  Tls.id='TLS'
  Tls.className='G'
  for (let i = 0; i < DATAV.iImagesetIDData.length; ++i) {
    let vx = DATAV.iImagesetIDData[i]
    Tls.appendChild(imageIndiv(vx[1], vx[2], vx[3]))
  }

  Mn.children[0].appendChild(Tls)
  generateRowsz()

}




