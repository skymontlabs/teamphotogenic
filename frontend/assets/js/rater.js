function generateRatingBlock() {
    // Main containers
    const RIaDiv = document.createElement('div');
    RIaDiv.className = 'RIa';

    const RDaDiv = document.createElement('div');
    RDaDiv.id = 'RDa';

    // RIa child elements
    const imgElement = document.createElement('img');
    imgElement.id = 'RIm'
    imgElement.src = "img/nirzu.jpg";
    imgElement.alt = "Rating picture";
    RIaDiv.appendChild(imgElement);




    // RDa child elements - Rating
    const ratingSpan = document.createElement('span');
    ratingSpan.className = 'fwHeavy';
    ratingSpan.textContent = 'Rating*';
    RDaDiv.appendChild(ratingSpan);


    // ratings
    const CaDiv = document.createElement('div');
    CaDiv.id = 'Ca';
    CaDiv.className = 'y z';

    const emojis = ['😒', '😐', '😃', '🤩', '🤑'];
    const ratings = ['Eh', 'Decent', 'Great', 'Stunning', 'Brilliant'];
    let ratingBtns = {}
    for (let index = 0; index < 5; ++index) {
        const button = document.createElement('button');
        let bid = `Rt${index}`
        button.id = bid;
        button.className = 'btn BR';


        const btnE = document.createElement('span');
        btnE.className = 'E'
        btnE.textContent = emojis[index];

        const btnT = document.createElement('span');
        btnT.textContent = ratings[index];

        button.appendChild(btnE);
        button.appendChild(btnT);
        ratingBtns[button] = index

        CaDiv.appendChild(button);
    }


    BUTTONS.HOME_RATES = ratingBtns
    RDaDiv.appendChild(CaDiv);





    // RDa child elements - Tags
    const tagsSpan = document.createElement('span');
    tagsSpan.className = 'fwHeavy';
    tagsSpan.textContent = 'Tags';
    RDaDiv.appendChild(tagsSpan);




//// prefer inline loops
    const UaDiv = document.createElement('div');
    UaDiv.id = 'Ua';

    const tags = ['😓 awkward', '🫥 bad expression', '🖼 bad framing', '🍞 bland', '🏟 distracting', '💨 blurry',
        '⚡️ bright', '🚊 busy', '🌈 colorful', '🕶 cool', '🌚 dark', '😬 forced smile', '🧂 grainy', '🚨 overedited',
        '🚶 poor posture', '🔭 too far away', '🔎 too close up'];

    tags.forEach((tag, index) => {
        const span = document.createElement('span');
        span.id = `Q${String.fromCharCode(97 + index)}`;
        span.className = 'BZ';
        span.textContent = tag;
        UaDiv.appendChild(span);
    });
    BUTTONS.HOME_TAGS = UaDiv

    RDaDiv.appendChild(UaDiv);

////

    // Comment section
    const commentSpan = document.createElement('span');
    commentSpan.className = 'fwHeavy';
    commentSpan.textContent = 'Comment';
    RDaDiv.appendChild(commentSpan);

    const textareaElement = document.createElement('textarea');
    textareaElement.id = 'CMa';
    textareaElement.placeholder = "This picture seems ...";
    textareaElement.tabIndex = '-1';
    textareaElement.maxLength = '255';
    RDaDiv.appendChild(textareaElement);

    const actionDiv = document.createElement('div');
    actionDiv.className = 'y z rel';

    const dotsBtn = document.createElement('button');
    dotsBtn.id = 'Dmo';
    dotsBtn.className = 'dots btn';
    ['d0', 'd1', 'd2'].forEach(dotClass => {
        const span = document.createElement('span');
        span.className = dotClass;
        dotsBtn.appendChild(span);
    });

    actionDiv.appendChild(dotsBtn);

    const ulElement = document.createElement('ul');
    ulElement.id = 'rMor';
    ulElement.className = 'dropsort';
    const liElement = document.createElement('li');
    const reportSpan = document.createElement('span');
    reportSpan.id = 'Rpt';
    reportSpan.textContent = 'Report image';
    liElement.appendChild(reportSpan);
    ulElement.appendChild(liElement);
    actionDiv.appendChild(ulElement);

    const buttonsDiv = document.createElement('div');
    buttonsDiv.className = 'y';
    buttonsDiv.id = 'prcd';

    const skipBtn = document.createElement('button');
    skipBtn.id = 'Sk';
    skipBtn.className = 'pointer y btn';
    const skipSpan = document.createElement('span');
    skipSpan.className = 'f11';
    skipSpan.textContent = 'Skip';
    skipBtn.appendChild(skipSpan);
    BUTTONS.HOME_SKIP = skipBtn
    buttonsDiv.appendChild(skipBtn);

    const submitBtn = document.createElement('button');
    submitBtn.id = 'Sm';
    submitBtn.className = 'pointer btn blue';
    const submitSpan = document.createElement('span');
    submitSpan.className = 'f11';
    submitSpan.textContent = 'Submit';
    submitBtn.appendChild(submitSpan);
    buttonsDiv.appendChild(submitBtn);
    BUTTONS.HOME_SUBMIT = submitBtn
    BUTTONS.HOME_PROCEED = buttonsDiv

    actionDiv.appendChild(buttonsDiv);
    RDaDiv.appendChild(actionDiv);

    // Append the main containers to the body or any other parent element
    Mn.appendChild(RIaDiv);
    Mn.appendChild(RDaDiv);
}




function getRater() {
  Mn.id = 'Ra'
  Mn.className = 'y'
  generateRatingBlock()
}
