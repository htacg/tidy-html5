---
title:    "Content"
bg:       "#9CFFD9"
color:    black    
style:    left
fa-icon:  wheelchair
---

# HTML Tidy Accessibility Checker

<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/testfiles.zip">(Download all testfiles here)</a>

<h2>Accessibility Checks Performed:</h2>

<p>
	<b>Error number [1.1.1.1] - Priority 1</b><br>
	All images -- including transparent gifs -- must have "alt" text. Alternate text should be concise (i.e. 10-12 words maximum). For transparent images and spacers, use alt="" (NULL), alt=" " (spaces are acceptable), or alt="blank". Any words depicted in the image should also appear in the "alt" text description.<br>
	<br>
	Testfile 1.1.1.f1: &lt;img&gt; missing "alt" text<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.1.2] - Priority 1</b><br>
	All images require text equivalents but "alt" text must also meet certain criteria otherwise it may be considered suspicious. For example, "alt" text may be deemed unacceptable if filenames and/or image file extensions (i.e. alt="xmas_tree.gif") are used in place of an actual text equivalent.<br>
	<br>
	Testfile 1.1.1.f2: suspicious "alt" text (filename)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.1.3] - Priority 1</b><br>
	All images require text equivalents but "alt" text must also meet certain criteria otherwise it may be considered suspicious. For example, "alt" text may be considered unacceptable if it is used to convey file size information (i.e. alt="650 bytes").<br>
	<br>
	Testfile 1.1.1.f3: suspicious "alt" text (file size)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.1.4] - Priority 1</b><br>
	All images require text equivalents but "alt" text must also meet certain criteria otherwise it may be considered suspicious. For example, using placeholder text (i.e. alt="image goes here") in place of an actual text equivalent is considered unacceptable.<br>
	<br>
	Testfile 1.1.1.f4: suspicious "alt" text (placeholder)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-1-f4.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.1.10] - Priority 1</b><br>
	All images require text equivalents but "alt" text must also meet certain criteria otherwise it may be considered suspicious. If "alt" text exceeds 150 characters, use the "longdesc" attribute along with a descriptive link (d-link) to describe the image.<br>
	<br>
	Testfile 1.1.1.f10: suspicious "alt" text (too long)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-1-f10.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-1-f10.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.1.11] - Priority 1</b><br>
	All images require text equivalents including those used to identify items in a list. If an image is used as a bullet, it should include the following "alt" text: alt="*" or alt="bullet".<br>
	<br>
	Testfile 1.1.1.f11: &lt;img&gt; missing "alt" text (bullet)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-1-f11.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-1-f11.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.1.12] - Priority 1</b><br>
	All images require text equivalents including those used to indicate breaks within a web page. If an image is used as a horizontal rule, it should include the following "alt" text: alt="*" or alt="horizontal rule".<br>
	<br>
	Testfile 1.1.1.f12: &lt;img&gt; missing "alt" text (horizontal rule)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-1-f12.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-1-f12.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.2.1] - Priority 1</b><br>
	If "alt" text cannot adequately describe an image's function or purpose, provide access to a more complete description via the "longdesc" attribute. Note you must also add a d-link (descriptive link) because many current browsers do not support the "longdesc" attribute. The advantage of including "longdesc" in current web documents is that the description will remain accessible when newer browsers deprecate d-links.<br>
	<br>
	Testfile 1.1.2.f1: &lt;img&gt; missing "longdesc" and d-link.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-2-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-2-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.2.2] - Priority 1</b><br>
	If "alt" text cannot adequately explain an image's function or purpose you must provide access to a more complete description. Because many current browsers do not support the "longdesc" attribute, including a d-link (descriptive link) ensures longer descriptions are accessible to all users.<br>
	<br>
	Testfile 1.1.2.f2: &lt;img&gt; missing "longdesc" and d-link.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-2-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-2-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.2.3] - Priority 1</b><br>
	If "alt" text cannot adequately describe an image's function or purpose, provide access to a more complete description via the "longdesc" attribute. Note you must also add a d-link (descriptive link) because many current browsers do not support the "longdesc" attribute. The advantage of including "longdesc" in current web documents is that the description will remain accessible when newer browsers deprecate d-links.<br>
	<br>
	Testfile 1.1.2.f3: &lt;img&gt; missing "longdesc" and d-link.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-2-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-2-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.3.1] - Priority 1</b><br>
	If an image is used as a button, it must include "alt" text. Do not describe the image itself but rather the destination or purpose of the link.<br>
	<br>
	Testfile 1.1.3.f1: &lt;img&gt; (button) missing "alt" text.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-3-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-3-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.4.1] - Priority 1</b><br>
	Applets must include alternate content to ensure the information is available to those who cannot access graphics. The alternate content should contain essentially the same information or serve a similar purpose as the applet itself. It may even be useful to describe the visual content or the sound effects accompanying the applet. You can either provide a link to a description or insert it directly into the document.<br>
	<br>
	Testfile 1.1.4.f1: &lt;applet&gt; missing alternate content.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-4-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-4-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.5.1] - Priority 1</b><br>
	Objects must include alternate content to ensure that the information is available to those who cannot access graphics. The alternate content should contain essentially the same information or serve a similar purpose to the object itself. You can either provide a link to a description or insert it directly into the document.<br>
	<br>
	Testfile 1.1.5.f1: &lt;object&gt; missing alternate content.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-5-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-5-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.6.1] - Priority 1</b><br>
	Web documents that contain audio files must also provide a text transcript that describes the sound or reproduces the content contained in the file. If the audio file contains an extensive amount of information, establish a link within the document that points to a complete text transcript of the sound file. This technique is suitable for reproducing song lyrics and excerpts from speeches.<br>
	<br>
	Testfile 1.1.6.f1: audio missing text transcript (wav)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-6-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-6-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.6.2] - Priority 1</b><br>
	Web documents that contain audio files must also provide a text transcript that describes the sound or reproduces the content contained in the file. If the audio file contains an extensive amount of information, establish a link within the document that points to a complete text transcript of the sound file. This technique is suitable for reproducing song lyrics and excerpts from speeches.<br>
	<br>
	Testfile 1.1.6.f2: audio missing text transcript (au)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-6-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-6-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.6.3] - Priority 1</b><br>
	Web documents that contain audio files must also provide a text transcript that describes the sound or reproduces the content contained in the file. If the audio file contains an extensive amount of information, establish a link within the document that points to a complete text transcript of the sound file. This technique is suitable for reproducing song lyrics and excerpts from speeches.<br>
	<br>
	Testfile 1.1.6.f3: audio missing text transcript (aiff)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-6-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-6-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.6.4] - Priority 1</b><br>
	Web documents that contain audio files must also provide a text transcript that describes the sound or reproduces the content contained in the file. If the audio file contains an extensive amount of information, establish a link within the document that points to a complete text transcript of the sound file. This technique is suitable for reproducing song lyrics and excerpts from speeches.<br>
	<br>
	Testfile 1.1.6.f4: audio missing text transcript (snd)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-6-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-6-f4.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.6.5] - Priority 1</b><br>
	Web documents that contain audio files must also provide a text transcript that describes the sound or reproduces the content contained in the file. If the audio file contains an extensive amount of information, establish a link within the document that points to a complete text transcript of the sound file. This technique is suitable for reproducing song lyrics and excerpts from speeches.<br>
	<br>
	Testfile 1.1.6.f5: audio missing text transcript (ra)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-6-f5.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-6-f5.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.6.6] - Priority 1</b><br>
	Web documents that contain audio files must also provide a text transcript that describes the sound or reproduces the content contained in the file. If the audio file contains an extensive amount of information, establish a link within the document that points to a complete text transcript of the sound file. This technique is suitable for reproducing song lyrics and excerpts from speeches.<br>
	<br>
	Testfile 1.1.6.f6: audio missing text transcript (rm)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-6-f6.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-6-f6.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.1.8.1] - Priority 1</b><br>
	If a frame cannot be adequately described in its title, include the "longdesc" attribute within the frame element to provide a link to additional information. The "longdesc" attribute can also be useful in helping to explain relationships between frames.<br>
	<br>
	Testfile 1.1.8.f1: &lt;frame&gt; may require "longdesc"<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-8-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-8-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.9.1] - Priority 1</b><br>
	You must include "alt" text for each &lt;area&gt; element within an image map. The "alt" text should indicate the destination of each link rather than provide a description of the image itself.<br>
	<br>
	Testfile 1.1.9.f1: &lt;area&gt; missing "alt" text.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-9-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-9-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.10.1] - Priority 1</b><br>
	A text equivalent must be provided for all scripts. Adding the &lt;noscript&gt; element to documents that include scripts ensures the information will be available in a text format if the client's browser does not support scripts.<br>
	<br>
	Testfile 1.1.10.f1: &lt;script&gt; missing &lt;noscript&gt; section.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-10-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-10-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.1.12.1] - Priority 1</b><br>
	Replace ascii art (illustrations created using keyboard symbols and characters) with actual images whenever possible. If the ascii artwork cannot be replaced, you must include an equivalent description to ensure the information is accessible to users who rely on audio-based and text-only browsers. A text equivalent is not required if the ascii image is explained in the document's content.<br>
	<br>
	Testfile 1.1.12.f1: ascii art requires description<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-1-12-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-1-12-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.2.1.1] - Priority 1</b><br>
	All server-side image maps must include redundant text links. Alt text is not available with server-side image maps unless redundant text links have been created. Redundant text links should describe the destination of each link (i.e. Home Page, Search Engine, etc.) rather than the actual image. If the map itself requires a explanation, use the "longdesc" attribute (and accompanying d-link) to provide a more detailed description.<br>
	<br>
	Testfile 1.2.1.f1: image map (server-side) requires text links.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [1.4.1.1] - Priority 1</b><br>
	All time-based multimedia presentations (i.e. movie clips, animations, slide shows) must include synchronized text equivalents for both the audio and visual content. If captions and visual descriptions are not synchronized with the main presentation, content can become confusing and potentially meaningless.<br>
	<br>
	Testfile 1.4.1.f1: multimedia requires synchronized text equivalents.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-4-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-4-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [1.5.1.1] - Priority 3</b><br>
	Client-side image maps also include redundant text links to ensure users will be able to navigate through a site. When creating redundant text links for image maps, create text that identifies the destination of each link (i.e. Home Page, Search Engine, etc.)<br>
	<br>
	Testfile 1.5.1.f1: image map (client-side) missing text links.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D1-5-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/1-5-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.1.1.1] - Priority 1</b><br>
	When information is conveyed using color, that information must also be made available through alternate means either through the context in which the information is presented or its markup properties. Ensure there is sufficient contrast between images and the background color.<br>
	<br>
	Testfile 2.1.1.1: ensure information not conveyed through color alone (image).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.1.1.2] - Priority 1</b><br>
	When information is conveyed using color, that information must also be made available through alternate means either through the context in which the information is presented or its markup properties. Ensure there is sufficient contrast between images and the background color.<br>
	<br>
	Testfile 2.1.1.2: ensure information not conveyed through color alone (applet).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.1.1.3] - Priority 1</b><br>
	When information is conveyed using color, that information must also be made available through alternate means either through the context in which the information is presented or its markup properties. Ensure there is sufficient contrast between images and the background color.<br>
	<br>
	Testfile 2.1.1.3: ensure information not conveyed through color alone (object).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-1-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-1-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.1.1.4] - Priority 1</b><br>
	When information is conveyed using color, that information must also be made available through alternate means either through the context in which the information is presented or its markup properties. Ensure there is sufficient contrast between images and the background color.<br>
	<br>
	Testfile 2.1.1.4: ensure information not conveyed through color alone (script).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-1-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-1-1-f4.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.1.1.5] - Priority 1</b><br>
	When information is conveyed using color, that information must also be made available through alternate means either through the context in which the information is presented or its markup properties. Ensure there is sufficient contrast between images and the background color.<br>
	<br>
	Testfile 2.1.1.5: ensure information not conveyed through color alone (input).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-1-1-f5.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-1-1-f5.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.2.1.1] - Priority 3</b><br>
	Ensure there is sufficient contrast between text and background colors for individuals with a color deficiency.<br>
	<br>
	Testfile 2.2.1.1: poor color contrast (text).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.2.1.2] - Priority 3</b><br>
	Ensure there is sufficient contrast between text and background colors for individuals with a color deficiency.<br>
	<br>
	Testfile 2.2.1.2: poor color contrast (link).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-2-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-2-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.2.1.3] - Priority 3</b><br>
	Ensure there is sufficient contrast between text and background colors for individuals with a color deficiency.<br>
	<br>
	Testfile 2.2.1.3: poor color contrast (active link).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-2-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-2-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [2.2.1.4] - Priority 3</b><br>
	Ensure there is sufficient contrast between text and background colors for individuals with a color deficiency.<br>
	<br>
	Testfile 2.2.1.4: poor color contrast (visited link).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D2-2-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/2-2-1-f4.html">Testfile</a>
</p>
<p>
	<b>Error number [3.2.1.1] - Priority 2</b><br>
	All documents must begin with a Document Type Declaration &lt;doctype&gt; or DTD. The informs a validator which version of HTML to use when verifying a document's syntax. The most commonly used DTD is HTML 4.01 Transitional.<br>
	<br>
	Testfile 3.2.1.1: &lt;doctype&gt; missing.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [3.3.1.1] - Priority 2</b><br>
	Use Cascading Style Sheets (CSS) to apply stylistic effects (i.e. font color, font size, paragraph indentation, etc.) and control positioning of content (i.e. page layout) within web documents.<br>
	<br>
	Testfile 3.3.1.1: use style sheets to control presentation.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-3-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-3-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [3.5.1.1] - Priority 2</b><br>
	Organize or "nest" headers in an ordered and logical fashion. Headers that are not structured in sequential order or those used to apply font effects can creating difficulties in navigation and comprehension for the visually impaired.<br>
	<br>
	Testfile 3.5.1.1: headers improperly nested.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-5-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-5-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [3.5.2.1] - Priority 2</b><br>
	If a lead sentence or paragraph is italicized consider converting it into a header. If a text element occurs within a paragraph and the paragraph is less than ten words containing only text items or formatting elements it is also potentially a header.<br>
	<br>
	Testfile 3.5.2.1: potential header (bold).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-5-2-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-5-2-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [3.5.2.2] - Priority 2</b><br>
	If a lead sentence or paragraph is italicized consider converting it into a header. If a text element occurs within a paragraph and the paragraph is less than ten words containing only text items or formatting elements it is also potentially a header.<br>
	<br>
	Testfile 3.5.2.2: potential header (italics).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-5-2-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-5-2-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [3.5.2.3] - Priority 2</b><br>
	If a lead sentence or paragraph is underlined consider converting it into a header. If a text element occurs within a paragraph and the paragraph is less than ten words containing only text items or formatting elements it is also potentially a header.<br>
	<br>
	Testfile 3.5.2.3: potential header (underline).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-5-2-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-5-2-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [3.6.1.1] - Priority 2</b><br>
	Avoid using list markup to create formatting effects. Do not use 'ul' (unordered list) to indent text, use Cascading Style Sheets (CSS) instead.<br>
	<br>
	Testfile 3.6.1.1: list usage invalid &lt;ul&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-6-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-6-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [3.6.1.2] - Priority 2</b><br>
	Avoid using list markup to create formatting effects. Do not use 'ol' (ordered list) to indent text, use Cascading Style Sheets (CSS) instead.<br>
	<br>
	Testfile 3.6.1.2: list usage invalid &lt;ol&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-6-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-6-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [3.6.1.4] - Priority 2</b><br>
	Avoid using list markup to create formatting effects. Do not use 'li' (list item) to indent text, use Cascading Style Sheets (CSS) instead.<br>
	<br>
	Testfile 3.6.1.4: list usage invalid &lt;li&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D3-6-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/3-6-1-f4.html">Testfile</a>
</p>
<p>
	<b>Error number [4.1.1.1] - Priority 1</b><br>
	Indicate changes in the primary language of a document through HTML markup. If changes in language are not marked, a speech synthesizer will attempt to pronounce a foreign word or phrase in the document's original primary language. Encapsulate short words or phrases with 'span lang="(indicate language here)" ' and use 'Q lang="(indicate language here)"' for quotes.<br>
	<br>
	Testfile 4.1.1.1: indicate changes in language.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D4-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/4-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [4.3.1.1] - Priority 3</b><br>
	Identify the primary language of each document to ensure that clients automatically retrieve web pages in their preferred language. Language can be specified either through http headers or html markup (i.e. 'html lang="en"').<br>
	<br>
	Testfile 4.3.1.1: language not identified.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D4-3-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/4-3-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [4.3.1.2] - Priority 3</b><br>
	Ensure the language specified in either the http header or html markup (i.e. 'html lang="en"') is valid.<br>
	<br>
	Testfile 4.3.1.2: language attribute invalid.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D4-3-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/4-3-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [5.1.2.1] - Priority 1</b><br>
	Data tables must include headers for each row and column. Use the "headers" attribute to attach labels to table rows and columns via the "id" attribute. This creates a link between headings and their associated data cells.<br>
	<br>
	Testfile 5.1.2.1: data &lt;table&gt; missing row/column headers (all).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-1-2-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-1-2-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [5.1.2.2] - Priority 1</b><br>
	Data tables must include headers for each row and column. Use the "headers" attribute to attach labels to table rows and columns via the "id" attribute. This creates a link between headings and their associated data cells.<br>
	<br>
	Testfile 5.1.2.2: data &lt;table&gt; missing row/column headers (1 col).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-1-2-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-1-2-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [5.1.2.3] - Priority 1</b><br>
	Data tables must include headers for each row and column. Use the "headers" attribute to attach labels to table rows and columns via the "id" attribute. This creates a link between headings and their associated data cells.<br>
	<br>
	Testfile 5.1.2.3: data &lt;table&gt; missing row/column headers (1 row).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-1-2-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-1-2-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [5.2.1.1] - Priority 1</b><br>
	If a data table has two or more logical levels of row or column headings, use html markup to link data cells with their corresponding headers. To identify groups of rows, use the 'thead', 'tfoot', and 'tbody' elements. To group columns, use 'col' and 'colgroup'.<br>
	<br>
	Testfile 5.2.1.1: data &lt;table&gt; may require markup (column headers).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [5.2.1.2] - Priority 1</b><br>
	If a data table has two or more logical levels of row or column headings, use html markup to link data cells with their corresponding headers. To identify groups of rows, use the 'thead', 'tfoot', and 'tbody' elements. To group columns, use the 'col' and 'colgroup' elements.<br>
	<br>
	Testfile 5.2.1.2: data &lt;table&gt; may require markup (row headers).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-2-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-2-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [5.3.1.1] - Priority 2</b><br>
	If tables are used for layout purposes ensure the content remains intelligible when the table is linearized (i.e. the content is converted into standard paragraphs). When tables are used to present text in word-wrapped, parallel columns the information may become jumbled when rendered by a screen reader.<br>
	<br>
	Testfile 5.3.1.1: verify layout talbes linearize properly.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-3-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-3-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [5.4.1.1] - Priority 2</b><br>
	Avoid using structural markup to apply style to text within data cells in tables used for layout purposes. Use Cascading Style Sheets (CSS) to format text, instead.<br>
	<br>
	Testfile 5.4.1.1: invalid markup used in layout &lt;table&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-4-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-4-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [5.5.1.1] - Priority 3</b><br>
	Tables must include a "summary" attribute in the table element. The summary should describe the relationship among table cells and cells that span multiple columns and/or rows. It is also useful in describing how the information contained in the table relates to other information in the document.<br>
	<br>
	Testfile 5.5.1.1: &lt;table&gt; missing summary.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-5-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-5-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [5.5.1.2] - Priority 3</b><br>
	Table summaries must include an actual value (i.e. summary="" or null is not acceptable). The summary should describe the relationship among table cells and cells that span multiple columns and/or rows. It is also useful in describing how the information contained in the table relates to other information in the document.<br>
	<br>
	Testfile 5.5.1.2: &lt;table&gt; summary invalid (null).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-5-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-5-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [5.5.1.3] - Priority 3</b><br>
	Table summaries must contain an actual value (i.e. summary=" " with spaces is not acceptable). The summary should describe the relationship among table cells and cells that span multiple columns and/or rows. It is also useful in describing how the information contained in the table relates to other information in the document.<br>
	<br>
	Testfile 5.5.1.3: &lt;table&gt; summary invalid (spaces).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-5-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-5-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [5.5.1.6] - Priority 3</b><br>
	Table summaries must contain an actual description. Placeholder text (i.e. summary="table summary") is not acceptable. The summary should describe the relationship among table cells and cells that span multiple columns and/or rows. It is also useful in describing how the information contained in the table relates to other information in the document.<br>
	<br>
	Testfile 5.5.1.6: &lt;table&gt; summary invalid (placeholder text).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-5-1-f6.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-5-1-f6.html">Testfile</a>
</p>
<p>
	<b>Error number [5.5.2.1] - Priority 2</b><br>
	Captions are used to describe the nature of the table in one to three sentences. Insert the caption below the table element. A caption is not always necessary. If a caption is not provided, use the "title" attribute to briefly describe the purpose of a table.<br>
	<br>
	Testfile 5.5.2.1: &lt;table&gt; summary &lt;caption&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-5-2-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-5-2-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [5.6.1.1] - Priority 3</b><br>
	Provide abbreviations for table headers to reduce useless repetition and reading time for those relying on screen readers and other speech technologies. Include the "abbr" attribute in the table's 'th' element and condense the heading to one or two key words.<br>
	<br>
	Testfile 5.6.1.1: &lt;table&gt; may require header abbreviations.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-6-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-6-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [5.6.1.2] - Priority 3</b><br>
	Abbreviations for table headers must contain an actual value (i.e. 'th abbr=""' is not acceptable). Condense the heading to one or two key words.<br>
	<br>
	Testfile 5.6.1.2: &lt;table&gt; header abbreviations invalid (null).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-6-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-6-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [5.6.1.3] - Priority 3</b><br>
	Abbreviations for table headers must contain an actual value (i.e. 'th abbr=" "' is not acceptable). Condense the heading to one or two key words.<br>
	<br>
	Testfile 5.6.1.3: &lt;table&gt; header abbreviations invalid (spaces).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D5-6-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/5-6-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.1.1.1] - Priority 1</b><br>
	If style sheets are used for formatting content and/or controlling page layout, be sure the information remains accessible when style sheets are disabled or not supported. Include a non-visual method of presenting the information and organize style sheets logically.<br>
	<br>
	Testfile 6.1.1.1: style sheets require testing (link).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.1.1.2] - Priority 1</b><br>
	If style sheets are used for formatting content and/or controlling page layout, be sure the information remains accessible when style sheets are disabled or not supported. Include a non-visual method of presenting the information and organize style sheets logically.<br>
	<br>
	Testfile 6.1.1.2: style sheets require testing (style element).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.1.1.3] - Priority 1</b><br>
	If style sheets are used for formatting content and/or controlling page layout, be sure the information remains accessible when style sheets are disabled or not supported. Include a non-visual method of presenting the information and organize style sheets logically.<br>
	<br>
	Testfile 6.1.1.3: style sheets require testing (style attribute).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-1-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-1-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [6.2.1.1] - Priority 1</b><br>
	Make the source of each frame a valid html document. If an image file is used as the source of a frame, you will not be able to include "alt" text with the graphic. Also, do not use the "title" attribute to describe the contents of a frame. If the content changes, the "title" will no longer be applicable.<br>
	<br>
	Testfile 6.2.1.1: &lt;frame&gt; source invalid.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.2.2.1] - Priority 1</b><br>
	Whenever dynamic content changes, text equivalents must also be updated. If an applet is used to generate dynamic content, provide a text equivalent between the opening and closing applet elements or via the "alt" attribute.<br>
	<br>
	Testfile 6.2.2.1: text equivalents require updating (applet).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-2-2-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-2-2-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.2.2.2] - Priority 1</b><br>
	Whenever dynamic content changes, text equivalents must also be updated. If a script is used to generate dynamic content, provide a text equivalent by including a &lt;noscript&gt; section in the document.<br>
	<br>
	Testfile 6.2.2.2: text equivalents require updating (script).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-2-2-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-2-2-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.2.2.3] - Priority 1</b><br>
	Whenever dynamic content changes, text equivalents must also be updated. If 'object' is used to generate dynamic content, include a text equivalent between the open and closing object elements.<br>
	<br>
	Testfile 6.2.2.3: text equivalents require updating (object).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-2-2-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-2-2-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.3.1.1] - Priority 1</b><br>
	Verify content remain accessible when programmatic objects are disabled or not supported. If a script is used to generate content, provide a text equivalent by including a &lt;noscript&gt; section in the document. Another option is to use server-side rather than client-side scripts. As a last resort, create a text-based alternative for the entire document.<br>
	<br>
	Testfile 6.3.1.1: programmatic objects require testing (script).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-3-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-3-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.3.1.2] - Priority 1</b><br>
	Verify content remain accessible when programmatic objects are disabled or not supported. If &lt;object&gt; is used to generate content, provide a text equivalent between the opening and closing object elements.<br>
	<br>
	Testfile 6.3.1.2: programmatic objects require testing (object).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-3-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-3-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.3.1.3] - Priority 1</b><br>
	Verify that content remains accessible when programmatic objects are disabled or not supported. This element allows different data types (i.e. movies, audio files, etc.) to be embedded in an html document. Regardless the data type, an appropriate text equivalent must also be included.<br>
	<br>
	Testfile 6.3.1.3: programmatic objects require testing (embed).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-3-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-3-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [6.3.1.4] - Priority 1</b><br>
	Verify content remain accessible when programmatic objects are disabled or not supported. If an applet is used to generate dynamic content, provide a text equivalent between the opening and closing applet elements or via the "alt" attribute.<br>
	<br>
	Testfile 6.3.1.1: programmatic objects require testing (applet).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-3-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-3-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [6.5.1.1] - Priority 2</b><br>
	Each &lt;frameset&gt; must include a valid &lt;noframes&gt; section which has at least one word of text or accessible html code and all links required to navigate the site. Do not use the &lt;noframes&gt; section to inform users that they must upgrade to a browser that supports frames.<br>
	<br>
	Testfile 6.5.1.1: &lt;frameset&gt; missing &lt;noframes&gt; section.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-5-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-5-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [6.5.1.2] - Priority 2</b><br>
	A valid &lt;noframes&gt; section includes at least one word of text or accessible html code and all links required to navigate the site. Do not use the &lt;noframes&gt; section to inform users that they must upgrade to a browser that supports frames.<br>
	<br>
	Testfile 6.5.1.2: &lt;noframes&gt; section invalid (no value).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-5-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-5-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [6.5.1.3] - Priority 2</b><br>
	Do not use the &lt;noframes&gt; section to inform users that they must upgrade to a browser that supports frames. A valid &lt;noframes&gt; section includes at least one word of text or accessible html code and all links required to navigate the site.<br>
	<br>
	Testfile 6.5.1.3: &lt;noframes&gt; section invalid (content).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-5-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-5-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [6.5.1.4] - Priority 2</b><br>
	All links must be enclosed in the &lt;noframes&gt; section. A valid &lt;noframes&gt; section has at least one word of text or accessible html code. In addition, &lt;noframes&gt; should not be used to inform users that they must upgrade to a browser that supports frames. Testfile 6.5.1.4: &lt;noframes&gt; section invalid (link).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D6-5-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/6-5-1-f4.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.1.1.1] - Priority 1</b><br>
	Ensure scripts do not cause on-screen flickering. It can trigger epileptic seizures in people with photosensitive epilepsy. At present, browsers do not allow screen flicker to be disabled by the user.<br>
	<br>
	Testfile 7.1.1.1: remove flicker (script).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.1.1.2] - Priority 1</b><br>
	Ensure objects do not cause on-screen flickering. It can trigger epileptic seizures in people with photosensitive epilepsy. At present, browsers do not allow screen flickering to be disabled by the user.<br>
	<br>
	Testfile 7.1.1.2: remove flicker (object).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.1.1.3] - Priority 1</b><br>
	Ensure embedded items such as movies, audio files, etc. do not cause on-screen flickering. It can trigger epileptic seizures in people with photosensitive epilepsy. At present, browsers do not allow screen flickering to be disabled by the user.<br>
	<br>
	Testfile 7.1.1.3: remove flicker (embed).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-1-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-1-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.1.1.4] - Priority 1</b><br>
	Ensure applets do not cause on-screen flickering. It can trigger epileptic seizures in people with photosensitive epilepsy. At present, browsers do not allow screen flickering to be disabled by the user.<br>
	<br>
	Testfile 7.1.1.4: remove flicker (applet).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-1-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-1-1-f4.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.1.1.5] - Priority 1</b><br>
	Ensure that animated gifs do not flicker. On-screen flickering can trigger epileptic seizures in people with photosensitive epilepsy. At present, browsers do not allow screen flickering to be disabled by the user.<br>
	<br>
	Testfile 7.1.1.5: remove flicker (animated gif).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-1-1-f5.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-1-1-f5.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.2.1.1] - Priority 2</b><br>
	Both &lt;blink&gt; and &lt;marquee&gt; are non-standard elements and should not be used in html documents. Use style sheets to emphasize content with special formatting (i.e. bold, italics, capitalization, underline, etc.)<br>
	<br>
	Testfile 7.2.1.1: remove blink/marquee.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.4.1.1] - Priority 2</b><br>
	Until browser agents allow clients to stop documents from automatically refreshing, avoid creating p ages that reload without a request from the user. Allow visitors to refresh or reload pages at their own discretion.<br>
	<br>
	Testfile 7.4.1.1: remove auto-refresh.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-4-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-4-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [7.5.1.1] - Priority 2</b><br>
	Avoid using markup that automatically redirects visitors to other web documents. People with limited vision or cognitive disabilities often don't have sufficient time to read a document that includes an auto-redirect command. Instead, create a link within the document that allows clients to advance to the next page at their own discretion.<br>
	<br>
	Testfile 7.5.1.1: remove auto-redirect.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D7-5-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/7-5-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [8.1.1.1] - Priority 1</b><br>
	Ensure pages are functional when programmatic objects such as scripts are disabled or not supported. Make scripts directly accessible or compatible with assistive technologies when functionality is important. Include a &lt;noscript&gt; section in the document and specify logical rather than device-dependent event handlers. As a last resort, provide equivalent content on an alternative page.<br>
	<br>
	Testfile 8.1.1.1: ensure programmatic objects are accessible (script).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D8-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/8-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [8.1.1.2] - Priority 1</b><br>
	Ensure pages are functional when programmatic objects are turned off or not supported. Use application-level triggers rather than user interaction-level event triggers. If device-dependent attributes must be used, provide redundant input mechanisms (i.e. specify two handlers for the same element). As a last resort, provide equivalent information on an alternative page.<br>
	<br>
	Testfile 8.1.1.2: ensure programmatic objects are accessible (object).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D8-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/8-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Warning number [8.1.1.3] - Priority 1</b><br>
	Ensure pages are functional when programmatic objects such as applets are disabled or not supported. Make applets directly accessible or compatible with assistive technologies when functionality is important. Provide either a link to a description or insert a text equivalent directly into the document and use event handlers that are input device-independent. As a last resort, provide equivalent information on an alternative page.<br>
	<br>
	Testfile 8.1.1.3: ensure programmatic objects are accessible (applet).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D8-1-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/8-1-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [8.1.1.4] - Priority 1</b><br>
	Ensure pages are functional when programmatic objects are disabled or not supported. Make embedded objects such as movies or audio files directly accessible or compatible with assistive technologies when functionality is important. Provide a text equivalent via "alt" and "longdesc" attributes or in element content. As a last resort, provide equivalent information on an alternative page.<br>
	<br>
	Testfile 8.1.1.4: ensure programmatic objects are accessible (embed).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D8-1-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/8-1-1-f4.html">Testfile</a>
</p>
<p>
	<b>Warning number [9.1.1.1] - Priority 1</b><br>
	Convert server-side image maps to client-side maps whenever possible. Client-side image maps are preferable because, unlike server-side maps, they can be accessed by individuals who either cannot view images, have chosen to use a non-graphical browser, or are unable to use traditional pointing devices (such as a mouse).<br>
	<br>
	Testfile 9.1.1.1: image map (server-side) requires conversion.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D9-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/9-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [9.3.1.1] - Priority 2</b><br>
	Include a redundant mechanism (such as keyboard input) if device dependent event handlers are used to invoke a script. The onMouseDown event handler should be paired and included in the same element with "onKeyDown".<br>
	<br>
	Testfile 9.3.1.1: &lt;script&gt; not keyboard accessible (onMouseDown).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D9-3-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/9-3-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [9.3.1.2] - Priority 2</b><br>
	Include a redundant mechanism (such as keyboard input) if device dependent event handlers are used to invoke a script. The onMouseUp event handler should be paired and included in the same element with "onKeyUp".<br>
	<br>
	Testfile 9.3.1.2: &lt;script&gt; not keyboard accessible (onMouseUp).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D9-3-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/9-3-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [9.3.1.3] - Priority 2</b><br>
	Include a redundant mechanism (such as keyboard input) if device dependent event handlers are used to invoke a script. The onMouseUp event handler should be paired and included in the same element with "onKeyPress".<br>
	<br>
	Testfile 9.3.1.3: &lt;script&gt; not keyboard accessible (onClick).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D9-3-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/9-3-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [9.3.1.4] - Priority 2</b><br>
	Always include a keyboard equivalent with a device dependent event handler such as a mouse. Avoid using event handlers that rely on mouse coordinates since this precludes device independent input. Scripts that accept keyboard input are generally accessible to those using speech input or a command line interface.<br>
	<br>
	Testfile 9.3.1.4: &lt;script&gt; not keyboard accessible (onMouseOver).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D9-3-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/9-3-1-f4.html">Testfile</a>
</p>
<p>
	<b>Error number [9.3.1.5] - Priority 2</b><br>
	Always include a keyboard equivalent with a device dependent event handler such as a mouse. Avoid using event handlers that rely on mouse coordinates since this precludes device independent input. Scripts that accept keyboard input are generally accessible to those using speech input or a command line interface.<br>
	<br>
	Testfile 9.3.1.5: &lt;script&gt; not keyboard accessible (onMouseOut).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D9-3-1-f5.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/9-3-1-f5.html">Testfile</a>
</p>
<p>
	<b>Error number [9.3.1.6] - Priority 2</b><br>
	Always include a keyboard equivalent with a device dependent event handler such as a mouse. Avoid using event handlers that rely on mouse coordinates since this precludes device independent input. Scripts that accept keyboard input are generally accessible to those using speech input or a command line interface.<br>
	<br>
	Testfile 9.3.1.6: &lt;script&gt; not keyboard accessible (onMouseMove).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D9-3-1-f6.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/9-3-1-f6.html">Testfile</a>
</p>
<p>
	<b>Warning number [10.1.1.1] - Priority 2</b><br>
	Do not cause pop-ups or other windows to appear and do not change the current window without informing the user. Avoid using target attributes such as "_new" or "_blank" in anchor elements. Use the existing window as the target. Links that open new windows can be disorienting to people with cognitive and visual disabilities.<br>
	<br>
	Testfile 10.1.1.1: new windows require warning (_new).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D10-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/10-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Warning number [10.1.1.2] - Priority 2</b><br>
	Do not cause pop-ups or other windows to appear and do not change the current window without informing the user. Avoid using target attributes such as "_blank" or "_new" in anchor elements. Use the existing window as the target. Links that open new windows can be disorienting to people with cognitive and visual disabilities.<br>
	<br>
	Testfile 10.1.1.2: new windows require warning (_blank).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D10-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/10-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [10.2.1.1] - Priority 2</b><br>
	Create a clear association between a form control and its label by ensuring labels are positioned properly within html markup. Do not separate a label from its form control with additional text, images, etc. If there are two or more controls on a single line, labels should be placed immediately before its corresponding control or place each label and control on a separate line.<br>
	<br>
	Testfile 10.2.1.1: &lt;label&gt; needs repositioning (&lt;label&gt; before &lt;input&gt;)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D10-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/10-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [10.2.1.2] - Priority 2</b><br>
	Create a clear association between a form control and its label by ensuring labels are positioned properly within html markup. Do not separate a form control from its label with additional text, images, etc. If there are two or more controls on a single line, labels should be placed immediately after its corresponding control or place each label and control on a separate line.<br>
	<br>
	Testfile 10.2.1.2: &lt;label&gt; needs repositioning (&lt;label&gt; after &lt;input&gt;)<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D10-2-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/10-2-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [10.4.1.1] - Priority 3</b><br>
	Include default text for all &lt;input&gt; form controls. Placing default text in form fields enables keyboard users to insert a cursor into placeholder text or characters and enter their own data.<br>
	<br>
	Testfile 10.4.1.1: form control requires default text.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D10-4-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/10-4-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [10.4.1.2] - Priority 3</b><br>
	Default text for all &lt;input&gt; form controls must include an actual value. Null (i.e. value="") is not valid default text but using placeholder characters (i.e. value="****") is acceptable. Placing default text in form fields enables keyboard users to insert a cursor into placeholder text and enter their own data.<br>
	<br>
	Testfile 10.4.1.2: form control default text invalid (null).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D10-4-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/10-4-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [10.4.1.3] - Priority 3</b><br>
	Default text for all &lt;input&gt; form controls must include an actual value. Including spaces (i.e. value=" ") in default text is not allowed but using placeholder characters (i.e. value="****") is acceptable. Placing default text in form fields enables keyboard users to insert a cursor into placeholder text and enter their own data.<br>
	<br>
	Testfile 10.4.1.3: form control default text invalid (spaces).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D10-4-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/10-4-1-f3.html">Testfile</a>
</p>
<p>
	<b>Warning number [11.2.1.1] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure their web pages remain compliant with the most current browser technologies. Applet (and all its attributes) has been deprecated in favor of &lt;object&gt;.<br>
	<br>
	Testfile 11.2.1.1: replace deprecated html &lt;applet&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.2] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;basefont&gt; element is deprecated. Use Cascading Style Sheets (CSS) to set font size.<br>
	<br>
	Testfile 11.2.1.2: replace deprecated html &lt;basefont&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.3] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;center&gt; element is deprecated. Use Cascading Style Sheets (CSS) to position text.<br>
	<br>
	Testfile 11.2.1.3: replace deprecated html &lt;center&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.4] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;dir&gt; element has been deprecated in favor of &lt;ul&gt; (unordered list).<br>
	<br>
	Testfile 11.2.1.4: replace deprecated html &lt;dir&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f4.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.5] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;font&gt; element is deprecated. Use Cascading Style Sheets (CSS) to set font size and color.<br>
	<br>
	Testfile 11.2.1.5: replace deprecated html &lt;font&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f5.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f5.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.6] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;isindex&gt; element (which creates a single-line text input control) has been deprecated. Use &lt;input&gt; to create text input controls instead.<br>
	<br>
	Testfile 11.2.1.6: replace deprecated html &lt;isindex&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f6.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f6.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.7] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;menu&gt; element has been deprecated in favor of &lt;ul&gt; (unordered list).<br>
	<br>
	Testfile 11.2.1.7: replace deprecated html &lt;menu&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f7.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f7.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.8] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;s&gt; element (used to render strike-through style text) has been deprecated. Use Cascading Style Sheets (CSS) to apply font effects to text.<br>
	<br>
	Testfile 11.2.1.8: replace deprecated html &lt;s&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f8.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f8.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.9] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;strike&gt; element (used to render strike-through style text) has been deprecated. Use Cascading Style Sheets (CSS) to apply font effects to text.<br>
	<br>
	Testfile 11.2.1.9: replace deprecated html &lt;striket&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f9.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f9.html">Testfile</a>
</p>
<p>
	<b>Error number [11.2.1.10] - Priority 2</b><br>
	Replace deprecated html elements and attributes to ensure web pages remain compliant with the most current browser technologies. The &lt;u&gt; element (which renders underlined text) has been deprecated. Use Cascading Style Sheets (CSS) to apply font effects to text.<br>
	<br>
	Testfile 11.2.1.10: replace deprecated html &lt;u&gt;.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D11-2-1-f10.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/11-2-1-f10.html">Testfile</a>
</p>
<p>
	<b>Error number [12.1.1.1] - Priority 1</b><br>
	Provide a title for each &lt;frame&gt; or &lt;iframe&gt; within a document. Frame titles must be meaningful (i.e. identify content and/or navigational links). Do not use filenames (e.g. title="frame1.html") or placeholder text (i.e. "insert frame title here") as a title.<br>
	<br>
	Testfile 12.1.1.1: &lt;frame&gt; missing title.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D12-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/12-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [12.1.1.2] - Priority 1</b><br>
	Frame titles must be meaningful (i.e. identify content and/or navigational links). Null (i.e. title="") is not an acceptable title. In addition, do not use filenames (e.g. title="frame1.html") or placeholder text (i.e. "insert frame title here") as a title.<br>
	<br>
	Testfile 12.1.1.2: &lt;frame&gt; title invalid (null).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D12-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/12-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [12.1.1.3] - Priority 1</b><br>
	Frame titles must be meaningful (i.e. identify content and/or navigational links). Spaces in a title (i.e. title=" ") are not acceptable. In addition, do not use filenames (e.g. title="frame1.html") or placeholder text (i.e. "insert frame title here") as a title.<br>
	<br>
	Testfile 12.1.1.3: &lt;frame&gt; title invalid (spaces).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D12-1-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/12-1-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [12.4.1.1]&lt; - Priority 2</b><br>
	The "for" and "id" attributes explicitly associate a label with its matching form control. The value of the "for" attribute must be identical to the "id" attribute. More than one label may be associated with the same control by creating multiple references through the "for" attribute.<br>
	<br>
	Testfile 12.4.1.1: associate labels explicitly with form controls.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D12-4-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/12-4-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [12.4.1.2] - Priority 2</b><br>
	The "for" attribute must accompany the "id" attribute to explicitly associate a label with its matching form control. The value of the "for" and "id" attributes must be identical. More than one label may be associated with the same control by creating multiple references via the "for" attribute.<br>
	<br>
	Testfile 12.4.1.2: associate labels explicitly with form controls (for).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D12-4-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/12-4-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [12.4.1.3] - Priority 2</b><br>
	The "id" attribute must accompany the "for" attribute to explicitly associate a label with its matching form control. The value of the "for" and "id" attributes must be identical. More than one label may be associated with the same control by creating multiple references via the "for" attribute.<br>
	<br>
	Testfile 12.4.1.3: associate labels explicitly with form controls (id).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D12-4-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/12-4-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [13.1.1.1] - Priority 2</b><br>
	Create link text that remains meaningful even when read out of context. Identify the purpose or target of each link (i.e. describe the destination of the link) and keep the text concise.<br>
	<br>
	Testfile 13.1.1.1: link text not meaningful.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-1-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-1-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [13.1.1.2] - Priority 2</b><br>
	Create link text that remains meaningful even when read out of context. Identify the purpose or target of each link (i.e. describe the destination of the link) and keep the text concise.<br>
	<br>
	Testfile 13.1.1.2: link text missing.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-1-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-1-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [13.1.1.3] - Priority 2</b><br>
	Keep link text concise. Create links that remain meaningful even when read out of context by clearly identifying the purpose or target of each link (i.e. describe the destination of the link).<br>
	<br>
	Testfile 13.1.1.3: link text too long .<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-1-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-1-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [13.1.1.4] - Priority 2</b><br>
	Avoid ambiguous link text such as "click here". In addition, the term "click" suggests the link is only accessible via a mouse or other similar pointing device. Create link text that remains meaningful even when read out of context. Identify the purpose or target of each link (i.e. describe the destination of the link)and keep the text concise.<br>
	<br>
	Testfile 13.1.1.4: link text not meaningful (click here).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-1-1-f4.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-1-1-f4.html">Testfile</a>
</p>
<p>
	<b>Error number [13.1.1.5] - Priority 2</b><br>
	Avoid ambiguous link text such as "more". Create link text that remains meaningful even when read out of context. Identify the purpose or target of each link (i.e. describe the destination of the link) and keep the text concise.<br>
	<br>
	Testfile 13.1.1.5: link text not meaningful (more).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-1-1-f5.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-1-1-f5.html">Testfile</a>
</p>
<p>
	<b>Error number [13.1.1.6] - Priority 2</b><br>
	Avoid ambiguous link text such as "follow this". Create link text that remains meaningful even when read out of context. Identify the purpose or target of each link (i.e. describe the destination of the link)and keep the text concise.<br>
	<br>
	Testfile 13.1.1.6: link text not meaningful (follow this).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-1-1-f6.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-1-1-f6.html">Testfile</a>
</p>
<p>
	<b>Error number [13.2.1.1] - Priority 2</b><br>
	Metadata should describe or provide specific information about individual web documents. Metadata is commonly used to list keywords so that search engines can conduct a more accurate and refined search. It can also include: content ratings, author information, site maps, stream channel definitions, a document's primary language, and digital library collections.<br>
	<br>
	Testfile 13.2.1.1: Metadata missing.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-2-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-2-1-f1.html">Testfile</a>
</p>
<p>
	<b>Error number [13.2.1.2] - Priority 2</b><br>
	If metadata is specified via the link element its value should be a URI. It should not be used to access style sheets. Use metadata to describe or provide specific information about individual web documents. Metadata often includes a list of keywords enabling search engines to conduct a more accurate and refined search. It can also contain content ratings, author information, site maps, stream channel definitions, a document's primary language, and digital library collections.<br>
	<br>
	Testfile 13.2.1.2: Metadata missing (link element).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-2-1-f2.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-2-1-f2.html">Testfile</a>
</p>
<p>
	<b>Error number [13.2.1.3] - Priority 2</b><br>
	Do not use the metadata element to refresh or redirect web pages automatically. Use metadata to describe or provide specific information about individual web documents. Metadata often includes a list of keywords enabling search engines to conduct a more accurate and refined search. It can also contain content ratings, author information, site maps, stream channel definitions, a document's primary language, and digital library collections.<br>
	<br>
	Testfile 13.2.1.3: Metadata missing (redirect/auto-refresh).<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-2-1-f3.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-2-1-f3.html">Testfile</a>
</p>
<p>
	<b>Error number [13.10.1.1] - Priority 3</b><br>
	Provide a means to skip over multi-line ascii art. Avoid ascii art (character illustrations) whenever possible. If ascii art must be used, provide a link to bypass the graphic. For ascii art 20 characters or less use the <abbr>element with the "title" attribute.<br>
	<br>
	Testfile 13.10.1.1: skip over ascii art.<br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/D13-10-1-f1.html">View testfile source</a><br>
	<a href="https://web.archive.org/web/20120417215657/http://www.aprompt.ca/Tidy/13-10-1-f1.html">Testfile</a></abbr>
</p>

