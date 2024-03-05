function genPhrase2(p2type) {
    pwdwrp.style.marginTop = '8px';
    pwdwrp.style.height = '56px';
    pwdwrp.style.opacity = '1';
    pwdwrp.style.visibility = 'visible';
}

function secondField() 
{
    const passwordDivWrapper = document.createElement('div');
    passwordDivWrapper.id = 'pwdwrp'
    passwordDivWrapper.style.margin = '8px 0 16px';
    passwordDivWrapper.style.height = '0';
    passwordDivWrapper.style.transition = '0.25s 0s ease height, 0.25s 0.2s ease opacity';
    passwordDivWrapper.style.opacity = '0';
    passwordDivWrapper.style.visibility = 'hidden';
    form.appendChild(passwordDivWrapper);

    const passwordLabel = document.createElement('label');
    passwordLabel.textContent = 'Password';
    passwordDivWrapper.appendChild(passwordLabel);

    const passwordDiv = document.createElement('div');
    passwordDiv.className = 'iS';
    passwordDivWrapper.appendChild(passwordDiv);

    const phrase2input = document.createElement('input');

    phrase2input.id = 'passwordSignup';
    phrase2input.name = 'password';
    phrase2input.type = 'password';
    phrase2input.placeholder = 'Password';
    phrase2input.style.width = '100%';
    phrase2input.style.boxSizing = 'border-box';
    passwordDiv.appendChild(phrase2input);
}

function showPassword() {
    passwordDivWrapper.className = 'show'
}

function showCode() {
    passwordDivWrapper.className = 'show'
    passwordLabel.textContent = 'Code'
}

function hideSecondField() {
    passwordDivWrapper.className = 'hidden'
}

function displayLoginError(txtLabel) {
    errorLabel.className = 'meta red show'
    errorLabel.textContent = txtLabel
}

function hideLoginError() {
    errorLabel.className = 'meta red'
    errorLabel.textContent = ''
}

function displayGenericErrorLogin() {
    displayLoginError('Server had an error')
}

function displayIncorrectPassword() {
    displayLoginError('Password is incorrect')
}

function displayIncorrectCode() {
    displayLoginError('Code is incorrect')
}

function switchTOTP()
{
    hideSecondField()

    emailLabel.textContent = 'Authenticator Code'
    emailSignup.type = 'number'
}

function genLogin() {
    Mn.id = 'Ya';
    Mn.children[0].className='x'

    const bgerDiv = document.createElement('canvas');
    bgerDiv.id = 'bger';
    bgerDiv.setAttribute('data-transition-in', '');
    Mn.appendChild(bgerDiv);

    const loginPanelDiv = document.createElement('div');
    loginPanelDiv.id = 'loginpanel';
    Mn.appendChild(loginPanelDiv);

    const h1 = document.createElement('h1');
    h1.style.fontSize = '20px';

    const signupTitleSpan = document.createElement('span');
    signupTitleSpan.id = 'signupTitle';
    signupTitleSpan.textContent = 'Sign up to get started';
    h1.appendChild(signupTitleSpan);

    const loginTitleSpan = document.createElement('span');
    loginTitleSpan.id = 'loginTitle';
    loginTitleSpan.textContent = 'Log in';
    h1.appendChild(loginTitleSpan);

    loginPanelDiv.appendChild(h1);

    const form = document.createElement('form');
    form.id = 'loginForm'
    loginPanelDiv.appendChild(form);

    const orDiv = document.createElement('div');
    form.appendChild(orDiv);

    const emailLabel = document.createElement('label');
    emailLabel.id = 'emailLabel'
    emailLabel.textContent = 'Phone or Email';
    form.appendChild(emailLabel);

    const emailDiv = document.createElement('div');
    emailDiv.className = 'iS';
    emailDiv.style.width = '100%';
    form.appendChild(emailDiv);

    const emailInput = document.createElement('input');
    emailInput.id = 'emailSignup';
    emailInput.setAttribute('autocomplete', 'email');
    emailInput.type = 'email';
    emailInput.placeholder = 'user@example.com';
    emailInput.style.width = '100%';
    emailInput.style.boxSizing = 'border-box';
    emailDiv.appendChild(emailInput);


//
    const passwordDivWrapper = document.createElement('div');
    passwordDivWrapper.id = 'pwdwrp'
    passwordDivWrapper.style.margin = '8px 0 16px';
    passwordDivWrapper.style.height = '0';
    passwordDivWrapper.style.transition = '0.25s 0s ease height, 0.25s 0.2s ease opacity';
    passwordDivWrapper.style.opacity = '0';
    passwordDivWrapper.style.visibility = 'hidden';
    form.appendChild(passwordDivWrapper);

    const passwordLabel = document.createElement('label');
    passwordLabel.textContent = 'Password';
    passwordDivWrapper.appendChild(passwordLabel);

    const passwordDiv = document.createElement('div');
    passwordDiv.className = 'iS';
    passwordDivWrapper.appendChild(passwordDiv);

    const phrase2input = document.createElement('input');

    phrase2input.id = 'passwordSignup';
    phrase2input.name = 'password';
    phrase2input.type = 'password';
    phrase2input.placeholder = 'Password';
    phrase2input.style.width = '100%';
    phrase2input.style.boxSizing = 'border-box';
    passwordDiv.appendChild(phrase2input);
// ends

//

    const signupButton = document.createElement('button');
    signupButton.id = 'signupeq';
    signupButton.textContent = 'Next';
    loginPanelDiv.appendChild(signupButton);

    const footerDiv = document.createElement('div');
    footerDiv.style.width = '100%';
    loginPanelDiv.appendChild(footerDiv);

    const errorLabel = document.createElement('label');
    errorLabel.className = 'meta red'
    errorLabel.id = 'errorLabel'
    footerDiv.appendChild(errorLabel);

    const termsDiv = document.createElement('div');
    termsDiv.className = 'PrPa';
    termsDiv.innerHTML = 'By signing up, you agree to our <a href="https://frame.io/terms/" target="_blank">Terms of Service</a> and <a href="https://frame.io/privacy" target="_blank">Privacy Policy.</a>';
    footerDiv.appendChild(termsDiv);

    const loginP = document.createElement('p');
    loginP.className = 'meta';
    loginP.innerHTML = 'Already have an account? <a href="/welcome">Log in.</a>';
    footerDiv.appendChild(loginP);

}

