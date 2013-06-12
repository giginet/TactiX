-- シーンの初期化時に一度だけ呼び出されます
function init(self)
end

-- シーンに入った時に一度だけ呼び出されます
function onEnter(self)
  local kawaz = CCSprite:create("dog.png") -- kawaz.pngというファイル名の画像を使ってSpriteを作成
  kawaz:setPosition(ccp(200, 500)) -- 作成したSpriteの中心座標を(100, 100)に設定
  self:addChild(kawaz) -- SpriteをSceneのNodeに追加
end

-- トランジションが終わった直後に呼び出されます
function onEnterTransitionDidFinish(self)
end

-- 毎フレーム呼び出されます
function update(self, dt)
end

-- シーンから出る時に一度だけ呼び出されます
function onExit(self)
end