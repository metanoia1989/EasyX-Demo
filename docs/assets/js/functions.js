
/**
 * 将HSV颜色转换为RGB颜色 
 * 
 * HSV（Hue, Saturation, Value）是一种表示颜色的模型
 * - Hue（色调）：颜色的类型，通常以度数表示，从0°到360°
 * - Saturation（饱和度）：颜色的鲜艳程度，从0%到100%。
 * - Value（明度）：颜色的亮度，从0%到100%。 
 * 
 * RGB（Red, Green, Blue）颜色模型表示颜色为红、绿、蓝三个分量，每个分量的范围是0到255
 * 
 * @param {*} h 
 * @param {*} s 
 * @param {*} v 
 * @returns 
 */
function HSVtoRGB(H, S, V) {
    let r, g, b;

    let i = Math.floor(H * 6);
    let f = H * 6 - i;
    let p = V * (1 - S);
    let q = V * (1 - f * S);
    let t = V * (1 - (1 - f) * S);

    switch (i % 6) {
        case 0:
            r = V;
            g = t;
            b = p;
            break;
        case 1:
            r = q;
            g = V;
            b = p;
            break;
        case 2:
            r = p;
            g = V;
            b = t;
            break;
        case 3:
            r = p;
            g = q;
            b = V;
            break;
        case 4:
            r = t;
            g = p;
            b = V;
            break;
        case 5:
            r = V;
            g = p;
            b = q;
            break;
    }

    // return {
    //     r: Math.round(r * 255),
    //     g: Math.round(g * 255),
    //     b: Math.round(b * 255)
    // };
    r = Math.round(r * 255);
    g = Math.round(g * 255);
    b = Math.round(b * 255);
    return rgbToHex(r, g, b);
}


/** 将一个颜色分量（0-255范围的整数）转换为两位16进制字符串 */
function componentToHex(c) {
    let hex = c.toString(16); // 将十进制数转换为16进制字符串
    return hex.length == 1 ? "0" + hex : hex; // 确保每个分量都是两位
}

/**
 * 接收RGB颜色的三个分量值（红、绿、蓝），转换为完整的16进制字符串 
 */
function rgbToHex(r, g, b) {
    return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b);
}


/**
 * 生成随机数 
 * @param {*} min 
 * @param {*} max 
 * @returns 
 */
function randomNum(min, max) {
    return Math.random() * (max - min) + min;
}
