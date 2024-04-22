
function generateIconRow() {
    // Create the main div
    const containerDiv = DIV.cloneNode(true);
    containerDiv.id = 'IcnRw';
    containerDiv.className = 'T16 t16 y z Bw oxh';

    // Create and append the images
    for (let i = 0; i < 7; i++) {
        const img = document.createElement('img');
        img.className = 'IElm';
        img.src = 'img/square.jpg';
        containerDiv.appendChild(img);
    }

    // Append the main div to the body or another parent element
    return containerDiv
}

function generateScoringaDiv() {
    const scoringaDiv = DIV.cloneNode(true);
    scoringaDiv.id = 'scoringa';
    scoringaDiv.className = 'T16 t16';

    const relDiv = DIV.cloneNode(true);
    relDiv.className = 'rel';
    relDiv.style.marginBottom = '2em';

    const yDiv = DIV.cloneNode(true);
    yDiv.className = 'y B16';

/*
    const pElement = document.createElement('p');
    pElement.textContent = 'Place a pill here allowing users to see either the pairing or rating vote but ONLY if there is BOTH';
    yDiv.appendChild(pElement);
*/


    const scoreSpan = document.createElement('span');
    scoreSpan.innerHTML = '<b>7.56</b> <span>avg score</span>';
    scoreSpan.style = 'line-height: 38px;';
    yDiv.appendChild(scoreSpan);

    const votesSpan = document.createElement('span');
    votesSpan.className = 'L16';
    votesSpan.innerHTML = '<b>43</b> <span>votes</span>';
    votesSpan.style = 'line-height: 38px;';
    yDiv.appendChild(votesSpan);

    const pilWrGenderDiv = document.createElement('div');
    pilWrGenderDiv.id = 'pGda';
    pilWrGenderDiv.className = 'pilWr mla y';
    const pilBgGenderDiv = document.createElement('div');
    pilBgGenderDiv.className = 'pilBg pointer';
    pilWrGenderDiv.appendChild(pilBgGenderDiv);

    ['Pairing', 'Rating'].forEach((gender, index) => {
        const pilItDiv = document.createElement('div');
        pilItDiv.id = ['Ff', 'Mf'][index];
        pilItDiv.className = 'pilIt pointer';
        pilItDiv.textContent = gender;
        pilWrGenderDiv.appendChild(pilItDiv);
    });

    yDiv.appendChild(pilWrGenderDiv);



    relDiv.appendChild(yDiv);

    const meterBDiv = DIV.cloneNode(true);
    meterBDiv.id = 'meterB';
    meterBDiv.style.cssText = 'width:100%;height:4px;background:rgba(0,2,40,0.1);border-radius: 4px;';

    const widths = [80, 75, 70, 65, 60];
    widths.forEach((width, index) => {
        const div = DIV.cloneNode(true);
        div.style.width = `${width}%`;
        div.id = `B${index}a`;
        div.className = 'meterEm abs';
        meterBDiv.appendChild(div);
    });

    relDiv.appendChild(meterBDiv);
    scoringaDiv.appendChild(relDiv);

    const rScoreDiv = DIV.cloneNode(true);
    rScoreDiv.className = 'rScore';
    rScoreDiv.style.cssText = 'padding-bottom: 1em;width: 100%;';

    const emojis = ['😒', '😐', '😃', '🤩', '🤑'];
    const counts = [5, 6, 9, 10, 25];
    const scoreTagWidths = ['10%', '10%', '10%', '20%', '60%'];

    emojis.forEach((emoji, index) => {
        const scoScDiv = DIV.cloneNode(true);
        scoScDiv.className = 'scoSc';

        const scoreBarDiv = DIV.cloneNode(true);
        scoreBarDiv.className = 'score-bar';
        scoScDiv.appendChild(scoreBarDiv);

        const scoreTagDiv = DIV.cloneNode(true);
        scoreTagDiv.className = 'score-tag';
        scoreTagDiv.style.width = `calc(${scoreTagWidths[index]} - ${index === 3 ? 14 : 7}px)`;
        scoScDiv.appendChild(scoreTagDiv);

        const tagNameSpan = document.createElement('span');
        tagNameSpan.className = 'tag-name';
        tagNameSpan.innerHTML = `<span class="E">${emoji}</span><span class="tc TR">${counts[index]}</span>`;
        scoScDiv.appendChild(tagNameSpan);

        rScoreDiv.appendChild(scoScDiv);
    });

    scoringaDiv.appendChild(rScoreDiv);
    return scoringaDiv
}

function generateRUa() {
    const containerDiv = DIV.cloneNode(true);
    containerDiv.className = 'RUa';

    const navigationDiv = DIV.cloneNode(true);
    navigationDiv.id = 'tIdNav';
    navigationDiv.className = 'partNav y BB';

    const navLinks = [
        { text: 'Images', href: '/tasks', class: 'active' },
        { text: 'Statistics', href: '/statistics', class: 'L16' },
        { text: 'Settings', href: '/settingsz', class: 'L16' }
    ];
    navLinks.forEach(linkInfo => {
        const link = document.createElement('a');
        link.className = linkInfo.class;
        link.href = linkInfo.href;
        link.textContent = linkInfo.text;
        navigationDiv.appendChild(link);
    });

    containerDiv.appendChild(navigationDiv);

    // Continue adding elements to the containerDiv for the entire structure...
    // For brevity, I'll skip some parts and give a summarized representation.

    const analyticsDiv = generateScoringaDiv()

    // ... add the child elements of analyticsDiv ...

    containerDiv.appendChild(analyticsDiv);

    const yzDiv = DIV.cloneNode(true);
    yzDiv.className = 'y z';

    const tagaaDiv = DIV.cloneNode(true);
    tagaaDiv.id = 'tagaa';
    tagaaDiv.style.cssText = 'margin-top: 0;width: 50%;display: none;';

    // ... add the child elements of tagaaDiv ...

    yzDiv.appendChild(tagaaDiv);
    containerDiv.appendChild(yzDiv);

    const commentaDiv = DIV.cloneNode(true);
    commentaDiv.id = 'commenta';
    commentaDiv.style.marginTop = '0';
    commentaDiv.style.display = 'none';

    // ... add the child elements of commentaDiv ...

    containerDiv.appendChild(commentaDiv);

    const ulElement = document.createElement('ul');
    ulElement.style.display = 'none';

    // ... add the list items to ulElement ...

    containerDiv.appendChild(ulElement);

    const premiumAnalyticsDiv = DIV.cloneNode(true);
    premiumAnalyticsDiv.id = 'PZa';

    // ... add the child elements of premiumAnalyticsDiv ...

    containerDiv.appendChild(premiumAnalyticsDiv);

    return containerDiv

}

function generateImageBl() {
    // Create the main div
    const containerDiv = DIV.cloneNode(true);
    containerDiv.className = 'ImU';

    // Create the image element
    const img = document.createElement('img');
    img.src = 'img/laurie.jpg';
    img.alt = 'Rating picture';
    containerDiv.appendChild(img);

    // Append the main div to the body or another parent element
    return containerDiv
}


function getImageID() {
  Mn.id='Ia'
  Mn.className='y z'
  let divX=Mn.children[0]
  divX.id = 'IIg'
  divX.className = ''
  
  /*
    <div class="ImW" style="width: calc(50% - 20px)">
      <!--<div id="RBa" style="background-image: url('img/laurie.jpg');"></div>-->
      <img src="img/laurie.jpg" alt="Rating picture">
    </div>
  */
// Example usage
  divX.appendChild(generateImageBl())
  divX.appendChild( generateIconRow())

  Mn.appendChild(generateRUa())
}

/*
<div id="Ia">
      <div class="x">
        <div class="y z">
          <div class="ImW" style="width: calc(50% - 20px)">
            <!--<div id="RBa" style="background-image: url('img/laurie.jpg');"></div>-->
            <img src="img/laurie.jpg" alt="Rating picture">
          </div>

          <div class="RUa" style="width: calc(50% - 20px);box-sizing: border-box;"> 
            <div id="tIdNav" class="partNav y BB">
              <a class="active" href="/tasks">Images</a>
              <a class="L16" href="/statistics">Statistics</a>
              <a class="L16" href="/settingsz">Settings</a>
            </div>
            <!--if we have analytics disabled-->
            <div id="scoringa" class="T16 t16">
              <div class="rel" style="margin-bottom: 2em">
                <div class="y" style="padding:0 0 8px;">
                  <p>Place a pill here allowing users to see either the pairing or rating vote but ONLY if there is BOTH</p>
                  <span><b>7.56</b> <span>avg score</span></span> <span class="L16"><b>43</b> <span>votes</span></span>
                </div>
                <div id="meterB" style="width:100%;height:4px;background:rgba(0,2,40,0.1);border-radius: 4px;">
                  <div style="width:80%;" id="B0a" class="meterEm abs"></div>
                  <div style="width:75%;" id="B1a" class="meterEm abs"></div>
                  <div style="width:70%;" id="B2a" class="meterEm abs"></div>
                  <div style="width:65%;" id="B3a" class="meterEm abs"></div>
                  <div style="width:60%;" id="B4a" class="meterEm abs"></div>
                </div>
              </div>

              <div class="rScore" style="padding-bottom: 1em;width: 100%;">
                <div class="scoSc">
                  <div class="score-bar"></div>
                  <div class="score-tag" style="width: calc(10% - 7px)"></div>
                  <span class="tag-name"><span class="E">😒</span><span class="tc TR"> (5)</span></span>
                </div>
                <div class="scoSc">
                  <div class="score-bar"></div>
                  <div class="score-tag" style="width: calc(10% - 7px)"></div>
                  <span class="tag-name"><span class="E">😐</span><span class="tc TR">(6)</span></span>
                </div>
                <div class="scoSc">
                  <div class="score-bar"></div>
                  <div class="score-tag" style="width: calc(10% - 7px)"></div>
                  <span class="tag-name"><span class="E">😃</span><span class="tc TR">(9)</span></span>
                </div>
                <div class="scoSc">
                  <div class="score-bar"></div>
                  <div class="score-tag" style="width: calc(20% - 14px)"></div>
                  <span class="tag-name"><span class="E">🤩</span><span class="tc TR">(10)</span></span>
                </div>
                <div class="scoSc">
                  <div class="score-bar"></div>
                  <div class="score-tag" style="width: calc(60% - 42px)"></div>
                  <span class="tag-name"><span class="E">🤑</span><span class="tc TR">(25)</span></span>
                </div>
              </div>

            </div>
            <div class="y z">
              <div id="tagaa"  style="margin-top: 0;width: 50%;display: none;">
                <h4>
                  <span class="hoverds dn">
                    <span>Red tags: < 20&#37; of users</span>
                    <span>yellow tags: < 20&#37; of users</span>
                    <span>green tags: 60&#37; of users selected this</span>
                  </span>
                </h4>
                <div>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">13</span> 😓 awkward</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">12</span> 🖼 bad framing</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">11</span> 🍞 bland</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">10</span> 💨 blurry</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">5</span> ⚡️ bright</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">4</span> 🚊 busy</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">4</span> 🌈 colorful</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">4</span> 🕶 cool</span></span>
                  <span class="wrap-tag"><span class="BZ"><span class="btn-ct">1</span> 🌚 dark</span></span>
                </div>
              </div>
            </div>
            <div id="commenta" style="margin-top: 0;display: none;">
              <h4>Comments</h4>
              <div id="CGa" style="overflow-x:hidden;overflow-y:scroll;height: auto;">
                <div class="comment"><span style="font-size:12px">So pretty ava</span><i>F, 32</i></div>
                <div class="comment"><span style="font-size:12px">Move the right side lefta</span><i>F, 32</i></div>
                <div class="comment"><span style="font-size:12px">That's a bit too gay</span><i>F, 32</i></div>
                <div class="comment"><span style="font-size:12px">Aubrey is kinda cute</span><i>F, 32</i></div>
                <div class="comment"><span style="font-size:12px">Do not include the other parts</span><i>F, 32</i></div>
              </div>
            </div>
            <!--if we have that enabled-->
            <ul style="display: none">
              <li>
                <h2></h2>
                <p>Males, on average, rated your pictures 50% higher than did females.</p>
              </li>
              <li>
                <p>Males, on average, rated your pictures 50% higher than did females.</p>
              </li>
              <li>
                <p>This picture was 40% more likely than , and 4% more likely than all pictures to get </p>
              </li>
              <li>Comments</li>
            </ul>
          </div>

          <!-- Premium analytics -->
          <div id="PZa">

          </div>
        </div>
        <div id="IcnRw" class="T16 t16 y z Bw" style="margin-top: 2em;">
          <img class="IElm" src="img/square.jpg">
          <img class="IElm" src="img/square.jpg">
          <img class="IElm" src="img/square.jpg">
          <img class="IElm" src="img/square.jpg">
          <img class="IElm" src="img/square.jpg">
          <img class="IElm" src="img/square.jpg">
          <img class="IElm" src="img/square.jpg">
        </div>
      </div>
    </div>
    */