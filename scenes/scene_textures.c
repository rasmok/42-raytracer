<scene>
	<camera>
		<positionXYZ>0 0 0</positionXYZ>
		<rotationXYZ>0 0 0</rotationXYZ>
	</camera>
	<objlist>
		<cobject>
			<transparency>0.5</transparency>
			<positionXYZ>0 0 5</positionXYZ>
			<rotationXYZ>0 0 0</rotationXYZ>
			<color> 0xFF0000 </color>
			<object name="sphere">
			</object>
		</cobject>
		<cobject>
			<positionXYZ>0 0 10</positionXYZ>
			<rotationXYZ>0 0 0</rotationXYZ>
			<color> 0x0000FF </color>
			<object name="sphere">
				<texture>resources/textures/earth2.bmp</texture>
			</object>
		</cobject>
		<cobject>
			<positionXYZ>0 5 10</positionXYZ>
			<rotationXYZ>0 0 0</rotationXYZ>
			<color> 0x0000FF </color>
			<object name="plane">
				<texture>resources/textures/texture2.bmp</texture>
			</object>
		</cobject>
	</objlist>
	<lightlist>
		<light type="point">
			<color>0xFFFFFF</color>
			<positionXYZ>0 0 0</positionXYZ>
			<intensity>1</intensity>
		</light>
	</lightlist>
	<ambientlight>
		<intensity>0.8</intensity>
	</ambientlight>
</scene>
