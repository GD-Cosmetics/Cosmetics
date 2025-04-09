import { Request, Response } from "express";

import {Router} from "websocket-express";
import { handleAccountPacket } from "../handlers/account";
import { handleCosmeticPacket } from "../handlers/cosmetics";

export const apiRouter = new Router();

apiRouter.get("/", (req: Request, res: Response) => {
    res.send("hi there cutie :3");
});

apiRouter.ws("/handlews", async (req, res) => {
	const ws = await res.accept();
	ws.on('message', (msg) => {
		const parsedMsg = JSON.parse(msg.toString())
		const packetID = parsedMsg["packetID"]
		if (packetID > 1000 && packetID < 2000) {
			handleAccountPacket(parsedMsg, ws);
		} else if (packetID > 2000 && packetID < 3000) {
			handleCosmeticPacket(parsedMsg, ws)
		}
	});
});