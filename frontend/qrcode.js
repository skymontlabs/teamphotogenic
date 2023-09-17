
function createBits() {
    let modules = new Uint8Array(SIZE * SIZE);
    let data = new Uint8Array();
    bb.appendBits(0b0100, 4);
    bb.appendBits(53, 8);   
    arr.append()



    drawFunctionPatterns();
    const vector<uint8_t> allCodewords = addEccAndInterleave(dataCodewords);
    drawCodewords(allCodewords);
    
    applyMask(6);  // Apply the final choice of mask
    drawFormatBits(6);  // Overwrite old format bits
}