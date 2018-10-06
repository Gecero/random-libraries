function toSupScript(text) {
	for(var i = 0; i < text.length; i++) {
		text = text.replace("A", "ᴬ").replace("B", "ᴮ").replace("D", "ᴰ").replace("E", "ᴱ").replace("G", "ᴳ").replace("H", "ᴴ").replace("I", "ᴵ").replace("J", "ᴶ").replace("K", "ᴷ").replace("L", "ᴸ").replace("M", "ᴹ").replace("N", "ᴺ").replace("O", "ᴼ").replace("P", "ᴾ").replace("R", "ᴿ").replace("T", "ᵀ").replace("U", "ᵁ").replace("V", "ⱽ").replace("a", "ᵃ").replace("b", "ᵇ").replace("c", "ᶜ").replace("d", "ᵈ").replace("e", "ᵉ").replace("f", "ᶠ").replace("g", "ᵍ").replace("h", "ʰ").replace("i", "ⁱ").replace("j", "ʲ").replace("k", "ᵏ").replace("l", "ˡ").replace("m", "ᵐ").replace("n", "ⁿ").replace("o", "ᵒ").replace("p", "ᵖ").replace("r", "ʳ").replace("s", "ˢ").replace("t", "ᵗ").replace("u", "ᵘ").replace("v", "ᵛ").replace("w", "ʷ").replace("x", "ˣ").replace("y", "ʸ").replace("z", "ᶻ").replace("0", "⁰").replace("1", "¹").replace("2", "²").replace("3", "³").replace("4", "⁴").replace("5", "⁵").replace("6", "⁶").replace("7", "⁷").replace("8", "⁸").replace("9", "⁹").replace("+", "⁺").replace("-", "⁻").replace("=", "⁼").replace("(", "⁽").replace(")", "⁾");
	}
	return text;
}

function toSubScript(text) {
	for(var i = 0; i < text.length; i++) {
		text = text.replace("a", "ₐ").replace("e", "ₑ").replace("h", "ₕ").replace("i", "ᵢ").replace("j", "ⱼ").replace("k", "ₖ").replace("l", "ₗ").replace("m", "ₘ").replace("n", "ₙ").replace("o", "ₒ").replace("p", "ₚ").replace("r", "ᵣ").replace("s", "ₛ").replace("t", "ₜ").replace("u", "ᵤ").replace("v", "ᵥ").replace("x", "ₓ").replace("0", "₀").replace("1", "₁").replace("2", "₂").replace("3", "₃").replace("4", "₄").replace("5", "₅").replace("6", "₆").replace("7", "₇").replace("8", "₈").replace("9", "₉").replace("+", "₊").replace("-", "₋").replace("=", "₌").replace("(", "₍").replace(")", "₎");			
	}
	return text;
}

function toFullWidth(text) {
	for(var i = 0; i < text.length; i++) {
		text = text.replace("A", "Ａ").replace("B", "Ｂ").replace("C", "Ｃ").replace("D", "Ｄ").replace("E", "Ｅ").replace("F", "Ｆ").replace("G", "Ｇ").replace("H", "Ｈ").replace("I", "Ｉ").replace("J", "Ｊ").replace("K", "Ｋ").replace("L", "Ｌ").replace("M", "Ｍ").replace("N", "Ｎ").replace("O", "Ｏ").replace("P", "Ｐ").replace("Q", "Ｑ").replace("R", "Ｒ").replace("S", "Ｓ").replace("T", "Ｔ").replace("U", "Ｕ").replace("V", "Ｖ").replace("W", "Ｗ").replace("X", "Ｘ").replace("Y", "Ｙ").replace("Z", "Ｚ").replace("a", "ａ").replace("b", "ｂ").replace("c", "ｃ").replace("d", "ｄ").replace("e", "ｅ").replace("f", "ｆ").replace("g", "ｇ").replace("h", "ｈ").replace("i", "ｉ").replace("j", "ｊ").replace("k", "ｋ").replace("l", "ｌ").replace("m", "ｍ").replace("n", "ｎ").replace("o", "ｏ").replace("p", "ｐ").replace("q", "ｑ").replace("r", "ｒ").replace("s", "ｓ").replace("t", "ｔ").replace("u", "ｕ").replace("v", "ｖ").replace("w", "ｗ").replace("x", "ｘ").replace("y", "ｙ").replace("z", "ｚ").replace("!", "！").replace("\"", "＂").replace("#", "＃").replace("$", "＄").replace("%", "％").replace("&", "＆").replace("'", "＇").replace("(", "（").replace(")", "）").replace("*", "＊").replace("+", "＋").replace(",", "，").replace("-", "－").replace(".", "．").replace("/", "／").replace("0", "０").replace("1", "１").replace("2", "２").replace("3", "３").replace("4", "４").replace("5", "５").replace("6", "６").replace("7", "７").replace("8", "８").replace("9", "９").replace(":", "：").replace(";", "；").replace("<", "＜").replace("=", "＝").replace(">", "＞").replace("@", "＠").replace("[", "［").replace("\\", "＼").replace("]", "］").replace("^", "＾").replace("_", "＿").replace("`", "｀").replace("{", "｛").replace("|", "｜").replace("}", "｝").replace("~", "～");
	}
	return text;
}

function toSmallCaps(text) {
	for(var i = 0; i < text.length; i++) {
		text = text.replace("a", "ᴀ").replace("b", "ʙ").replace("c", "ᴄ").replace("d", "ᴅ").replace("e", "ᴇ").replace("f", "ғ").replace("g", "ɢ").replace("h", "ʜ").replace("i", "ɪ").replace("j", "ᴊ").replace("k", "ᴋ").replace("l", "ʟ").replace("m", "ᴍ").replace("n", "ɴ").replace("o", "ᴏ").replace("p", "ᴘ").replace("q", "ǫ").replace("r", "ʀ").replace("s", "s").replace("t", "ᴛ").replace("u", "ᴜ").replace("v", "ᴠ").replace("w", "ᴡ").replace("x", "x").replace("y", "ʏ").replace("z", "ᴢ");
	}
	return text;
}
