import * as fs from "fs";

const input = fs.readFileSync(0, "utf-8").trim().split(/\s+/);
let i = 0;

const s = input[i++];
const n = s.length;
let answer = 0;

for (let j = 0; j < n; j++) {
    if (s[j] == 'i' || s[j] == 'j') {
        answer++;
    }
}

console.log(answer);