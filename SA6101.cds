<distribution version="17.0.0" name="SA6101" type="MSI">
	<prebuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></prebuild>
	<postbuild>
		<workingdir>workspacedir</workingdir>
		<actions></actions></postbuild>
	<msi GUID="{FB3C132E-F904-4095-80DA-5509B961C0A4}">
		<general appName="SA6101" outputLocation="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\cvidistkit.SA6101" relOutputLocation="cvidistkit.SA6101" outputLocationWithVars="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\cvidistkit.%name" relOutputLocationWithVars="cvidistkit.%name" upgradeBehavior="1" autoIncrement="true" version="1.0.19">
			<arp company="Microsoft" companyURL="" supportURL="" contact="" phone="" comments=""/>
			<summary title="" subject="" keyWords="" comments="" author=""/></general>
		<userinterface language="English" showPaths="true" showRuntimeOnly="true" readMe="" license="">
			<dlgstrings welcomeTitle="SA6101" welcomeText=""/></userinterface>
		<dirs appDirID="101">
			<installDir name="SA6101" dirID="100" parentID="7" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="SA6101" dirID="101" parentID="2" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="updates" dirID="102" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="softwareFileBackups" dirID="103" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Uir" dirID="104" parentID="103" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Resource" dirID="105" parentID="103" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="hardFileBackups" dirID="106" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="SA6101" dirID="107" parentID="101" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Data" dirID="108" parentID="107" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="Resource" dirID="109" parentID="107" isMSIDir="false" visible="true" unlock="false"/>
			<installDir name="[Start&gt;&gt;Programs]" dirID="7" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Desktop]" dirID="0" parentID="-1" isMSIDir="true" visible="true" unlock="false"/>
			<installDir name="[Program Files]" dirID="2" parentID="-1" isMSIDir="true" visible="true" unlock="false"/></dirs>
		<files>
			<simpleFile fileID="0" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V_Bias.ico" relSourcePath="Resource\V_Bias.ico" relSourceBase="0" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="1" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\bg_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="2" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\GND.ico" relSourcePath="Resource\GND.ico" relSourceBase="0" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="3" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Drain.png" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="4" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V.ico" relSourcePath="Resource\V.ico" relSourceBase="0" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="5" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\6010.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="6" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Save_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="7" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\0b5f76e6304de51436b2a3c882ad751.bmp" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="8" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R.bmp" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="9" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\D-ouGraph.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="10" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\DoubleGraph.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="11" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Drain_pressed.png" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="12" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\single_ico.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="13" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\SA5102.jpg" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="14" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Graph_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="15" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Graph.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="16" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Arrow.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="17" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I_I.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="18" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\single.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="19" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Settings.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="20" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Tools.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="21" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Table_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="22" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V_Step.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="23" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\bg_press.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="24" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Stop.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="25" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Projects.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="26" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I_Bias.ico" relSourcePath="Resource\I_Bias.ico" relSourceBase="0" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="27" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="28" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R_Bias.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="29" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\print.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="30" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\no.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="31" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Configure_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="32" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\sofot.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="33" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Wbg.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="34" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Table.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="35" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Configure.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="36" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\right.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="37" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\analyze.ico" relSourcePath="Resource\analyze.ico" relSourceBase="0" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="38" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Projects.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="39" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\analyze.ico" relSourcePath="Resource\analyze.ico" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="40" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Drain.png" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="41" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\FET_ico.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="42" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Run.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="43" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I.ico" relSourcePath="Resource\I.ico" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="44" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Graph.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="45" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\no.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="46" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\6010.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="47" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Id-Vds Configuration.uir" relSourcePath="UI Files\Panel\Id-Vds Configuration.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="48" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\R-T.uir" relSourcePath="UI Files\Panel\R-T.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="49" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\TerminalPanel.uir" relSourcePath="UI Files\Panel\TerminalPanel.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="50" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Settings.uir" relSourcePath="UI Files\Panel\Settings.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="51" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\AutoSaveData.uir" relSourcePath="UI Files\Panel\AutoSaveData.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="52" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Project.uir" relSourcePath="UI Files\Panel\Project.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="53" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Sample Configuration.uir" relSourcePath="UI Files\Panel\Sample Configuration.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="54" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Experiment List.uir" relSourcePath="UI Files\Panel\Experiment List.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="55" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\I-T.uir" relSourcePath="UI Files\Panel\I-T.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="56" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Id-Vgs Configuration.uir" relSourcePath="UI Files\Panel\Id-Vgs Configuration.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="57" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Table.uir" relSourcePath="UI Files\Panel\Table.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="58" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Id-t Configuration.uir" relSourcePath="UI Files\Panel\Id-t Configuration.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="59" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\ResultDispPanel.uir" relSourcePath="UI Files\Panel\ResultDispPanel.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="60" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Result Menu.uir" relSourcePath="UI Files\Panel\Result Menu.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="61" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Terminal.uir" relSourcePath="UI Files\Panel\Terminal.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="62" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\FET.ico" relSourcePath="Resource\FET.ico" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="63" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="64" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\0b5f76e6304de51436b2a3c882ad751.bmp" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="65" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Graph_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="66" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\SA5102.jpg" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="67" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R_ico.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="68" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Arrow.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="69" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\single.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="70" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\RunAgain.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="71" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Configure.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="72" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R_Bias.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="73" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\print_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="74" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\print.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="75" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Select_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="76" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\saveData.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="77" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\print_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="78" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\SA6101.png" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="79" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\saveData_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="80" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\FET.ico" relSourcePath="Resource\FET.ico" relSourceBase="0" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="81" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Run.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="82" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\R-T.uir" relSourcePath="UI Files\Panel\R-T.uir" relSourceBase="0" targetDir="108" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="83" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\MainPanel.uir" relSourcePath="UI Files\Panel\MainPanel.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="84" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Id-t Configuration.uir" relSourcePath="UI Files\Panel\Id-t Configuration.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="85" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Terminal.uir" relSourcePath="UI Files\Panel\Terminal.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="86" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\ResultDispPanel.uir" relSourcePath="UI Files\Panel\ResultDispPanel.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="87" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Experiment List.uir" relSourcePath="UI Files\Panel\Experiment List.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="88" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Select.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="89" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\I-V.uir" relSourcePath="UI Files\Panel\I-V.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="90" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Environment.uir" relSourcePath="UI Files\Panel\Environment.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="91" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Result Menu.uir" relSourcePath="UI Files\Panel\Result Menu.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="92" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\TerminalPanel.uir" relSourcePath="UI Files\Panel\TerminalPanel.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="93" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Sample Configuration.uir" relSourcePath="UI Files\Panel\Sample Configuration.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="94" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\AutoSaveData.uir" relSourcePath="UI Files\Panel\AutoSaveData.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="95" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Tools.uir" relSourcePath="UI Files\Panel\Tools.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="96" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\RunAgain.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="97" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I-I.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="98" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Save.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="99" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Pic.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="100" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\bg.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="101" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\FET_ico.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="102" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\gate.png" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="103" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R_ico.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="104" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\gate_pressed.png" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="105" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\BTN.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="106" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Analyze_pressed.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="107" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I.ico" relSourcePath="Resource\I.ico" relSourceBase="0" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="108" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V_I.ico" targetDir="109" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="109" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Tools.uir" relSourcePath="UI Files\Panel\Tools.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="110" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\MainPanel.uir" relSourcePath="UI Files\Panel\MainPanel.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="111" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\updates\updateInfo.xml" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="112" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\updates\localInfo.xml" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="113" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Environment.uir" relSourcePath="UI Files\Panel\Environment.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="114" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\updates\replace.exe" targetDir="102" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="115" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\I-V.uir" relSourcePath="UI Files\Panel\I-V.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="116" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\GraphDisp.uir" relSourcePath="UI Files\Panel\GraphDisp.uir" relSourceBase="0" targetDir="104" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="117" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Analyze_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="118" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V.ico" relSourcePath="Resource\V.ico" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="119" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Table_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="120" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Configure_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="121" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Tools.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="122" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\D-ouGraph.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="123" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Save_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="124" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\SA6101.png" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="125" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I-I.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="126" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Table.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="127" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V_Bias.ico" relSourcePath="Resource\V_Bias.ico" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="128" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V_I.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="129" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I_Bias.ico" relSourcePath="Resource\I_Bias.ico" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="130" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\right.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="131" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\BTN.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="132" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\saveData_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="133" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Select.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="134" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\bg_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="135" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Select_pressed.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="136" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\V_Step.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="137" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Settings.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="138" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Stop.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="139" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\I_I.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="140" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\sofot.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="141" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Settings.uir" relSourcePath="UI Files\Panel\Settings.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="142" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\single_ico.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="143" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\I-T.uir" relSourcePath="UI Files\Panel\I-T.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="144" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Id-Vds Configuration.uir" relSourcePath="UI Files\Panel\Id-Vds Configuration.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="145" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\GraphDisp.uir" relSourcePath="UI Files\Panel\GraphDisp.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="146" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\cvibuild.SA6101\Release\SA6101.exe" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="147" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Wbg.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="148" sourcePath="E:\GitWorkplace\Sinoagg\Software\hardFileBackups\SA6101.bin" targetDir="106" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="149" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Table.uir" relSourcePath="UI Files\Panel\Table.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="150" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\R.bmp" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="151" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\saveData.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="152" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\R-T.uir" relSourcePath="UI Files\Panel\R-T.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="153" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\bg_press.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="154" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Id-Vgs Configuration.uir" relSourcePath="UI Files\Panel\Id-Vgs Configuration.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="155" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\GND.ico" relSourcePath="Resource\GND.ico" relSourceBase="0" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="156" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\gate_pressed.png" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="157" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Pic.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="158" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\bg.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="159" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\DoubleGraph.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="160" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\gate.png" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="161" sourcePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\UI Files\Panel\Project.uir" relSourcePath="UI Files\Panel\Project.uir" relSourceBase="0" targetDir="107" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="162" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Drain_pressed.png" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/>
			<simpleFile fileID="163" sourcePath="E:\GitWorkplace\Sinoagg\Software\SA6101_realTime\Resource\Save.ico" targetDir="105" readonly="false" hidden="false" system="false" regActiveX="false" runAfterInstallStyle="IMMEDIATELY_RESUME_INSTALL" cmdLineArgs="" runAfterInstall="false" uninstCmdLnArgs="" runUninst="false"/></files>
		<fileGroups>
			<projectOutput targetType="0" dirID="107" projectID="0">
				<fileID>146</fileID></projectOutput>
			<projectDependencies dirID="107" projectID="0"/></fileGroups>
		<shortcuts>
			<shortcut name="SA6101" targetFileID="146" destDirID="2" cmdLineArgs="" description="" runStyle="NORMAL"/>
			<shortcut name="SA6101" targetFileID="146" destDirID="0" cmdLineArgs="" description="" runStyle="NORMAL"/></shortcuts>
		<mergemodules>
			<nireports></nireports>
			<graph3d></graph3d></mergemodules>
		<products>
			<product name="NI LabVIEW Runtime 2017" UC="{620DBAE1-B159-4204-8186-0813C8A6434C}" productID="{AF2FEF05-E895-4750-8F69-B5FA5388B2A3}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49153">
				<cutSoftDeps/></product>
			<product name="NI LabWindows/CVI Shared Runtime 2017" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{28BFBCB6-5EEE-47F1-A894-FCD877057827}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49157">
				<cutSoftDeps/></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime 2017" UC="{3047BAC4-D68B-48CB-838D-2E10761B01BA}" productID="{7D090F57-E9A4-4229-9911-CC352128D3F5}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49155"/>
			<product name="NI Launcher" UC="{7FB990C5-1A51-4C1D-99C4-C6E50368E105}" productID="{2C151359-0420-401D-9408-6523BE6C3EE8}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49154"/>
			<product name="NI TDM Excel Add-In" UC="{6D2EBDAF-6CCD-44F3-B767-4DF9E0F2037B}" productID="{9DFD2D10-299D-4A37-9267-4F28E974F403}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49155"/>
			<product name="NI Variable Engine 2017" UC="{EB7A3C81-1C0F-4495-8CE5-0A427E4E6285}" productID="{3011FA37-DCC4-4BF8-8900-12D68EC7996F}" path="C:\ProgramData\National Instruments\MDF\ProductCache\" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49152"/></products>
		<runtimeEngine installToAppDir="false" activeXsup="false" analysis="true" cvirte="true" dotnetsup="true" instrsup="true" lowlevelsup="true" lvrt="true" netvarsup="true" rtutilsup="false">
			<hasSoftDeps/>
			<doNotAutoSelect>
			<component>activeXsup</component>
			<component>rtutilsup</component>
			</doNotAutoSelect></runtimeEngine><sxsRuntimeEngine>
			<selected>true</selected>
			<doNotAutoSelect>false</doNotAutoSelect></sxsRuntimeEngine>
		<advanced mediaSize="650">
			<launchConditions>
				<condition>MINOS_WIN7_SP1</condition>
			</launchConditions>
			<includeConfigProducts>true</includeConfigProducts>
			<maxImportVisible>silent</maxImportVisible>
			<maxImportMode>merge</maxImportMode>
			<custMsgFlag>false</custMsgFlag>
			<custMsgPath>msgrte.txt</custMsgPath>
			<signExe>false</signExe>
			<certificate></certificate>
			<signTimeURL></signTimeURL>
			<signDescURL></signDescURL></advanced>
		<baselineProducts>
			<product name="NI LabVIEW Runtime 2017" UC="{620DBAE1-B159-4204-8186-0813C8A6434C}" productID="{AF2FEF05-E895-4750-8F69-B5FA5388B2A3}" path="(None)" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49153">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{214BEF10-ED6E-4198-A7EC-893BC3550330}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{36E48952-DC01-4739-848E-EA7DC71FB485}</productID>
					<productID>{3F73C183-4720-43B3-8181-71F55B35DE16}</productID>
					<productID>{405BA31C-3A17-47EC-9075-D18B09387C32}</productID>
					<productID>{40600E36-4921-4A62-8A07-4503C6855A66}</productID>
					<productID>{4CDCD50F-CFCA-40FB-892A-90F526537273}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5DF6BA6E-A045-48FC-9AD8-39A0799FA79B}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6E6C89C3-648D-4E5C-BF2E-1534F79D2FA7}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{7A92E288-9EFF-47D2-9A44-CF00F363DA7D}</productID>
					<productID>{7BBC9D71-9E93-4E87-A529-1CAC4537175C}</productID>
					<productID>{8301A002-940A-4588-A760-043776F1CA6E}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{B7685AF0-3026-43FA-A953-327C2185BAAF}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{E6891F9D-6730-4D5D-B513-1B70EDB84566}</productID>
					<productID>{E6E0A909-7F30-4EE8-A493-F0329B57B187}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Shared Runtime 2017" UC="{80D3D303-75B9-4607-9312-E5FC68E5BFD2}" productID="{28BFBCB6-5EEE-47F1-A894-FCD877057827}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49157">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{13774AE4-124D-48C2-A8AC-F8070918385E}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{2D894BCB-6069-418C-BF94-8E5915D8867C}</productID>
					<productID>{2FC99AB8-F11D-4938-B14F-AC60D1016FE7}</productID>
					<productID>{35E63DC2-6BCC-48D6-A1C5-5B068DF34117}</productID>
					<productID>{4A548403-7448-4B6D-8A8E-F41F53AE4A3F}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5E99102B-D07A-4D85-8D50-4BE55E3633A0}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{BEA1952D-1F00-4336-9A76-C41FA181C02D}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{D4E86102-76C1-458C-B0C2-F42B43CAD3CC}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DBAAC357-96E7-459F-B115-B14E29F652EF}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF35E2A2-9214-4B76-91AE-5567076AAE8C}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime 2017" UC="{3047BAC4-D68B-48CB-838D-2E10761B01BA}" productID="{7D090F57-E9A4-4229-9911-CC352128D3F5}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49155">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{12DD771D-D906-470D-83D8-E443B3726E65}</productID>
					<productID>{13774AE4-124D-48C2-A8AC-F8070918385E}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{4A548403-7448-4B6D-8A8E-F41F53AE4A3F}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{646B4AEC-1DCD-450D-A27E-2FCC02CC071D}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{81CF68C8-142B-443E-9B96-0B38E2997D88}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{ACA04902-B834-4355-88DA-ECDC9EA75900}</productID>
					<productID>{BCFF276A-C527-4D21-AB9B-2EE8ABB9430C}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D0078EF1-0008-4D30-83AF-4C56D2516E55}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{D4E86102-76C1-458C-B0C2-F42B43CAD3CC}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DBAAC357-96E7-459F-B115-B14E29F652EF}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID></dependencies></product>
			<product name="NI Launcher" UC="{7FB990C5-1A51-4C1D-99C4-C6E50368E105}" productID="{2C151359-0420-401D-9408-6523BE6C3EE8}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49154">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID></dependencies></product>
			<product name="NI LabWindows/CVI Side-By-Side Runtime (Current Version)" UC="{CF830703-BC3D-4feb-891F-6FF27153C204}" productID="{7D090F57-E9A4-4229-9911-CC352128D3F5}" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="17.0.49155">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{12DD771D-D906-470D-83D8-E443B3726E65}</productID>
					<productID>{13774AE4-124D-48C2-A8AC-F8070918385E}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{18C5DCAB-EF32-48F8-9789-2A33DE1CA2CB}</productID>
					<productID>{29FBD1D9-6A19-4CF6-935F-C0EFCFB6CA3D}</productID>
					<productID>{4A548403-7448-4B6D-8A8E-F41F53AE4A3F}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{646B4AEC-1DCD-450D-A27E-2FCC02CC071D}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{81CF68C8-142B-443E-9B96-0B38E2997D88}</productID>
					<productID>{A4FAF873-938B-43B8-BBF2-E4B2C0CE730B}</productID>
					<productID>{ACA04902-B834-4355-88DA-ECDC9EA75900}</productID>
					<productID>{BCFF276A-C527-4D21-AB9B-2EE8ABB9430C}</productID>
					<productID>{CE7D38A4-66ED-4D33-A385-D4A2CF4BFF81}</productID>
					<productID>{D0078EF1-0008-4D30-83AF-4C56D2516E55}</productID>
					<productID>{D357A74D-E186-4E4B-AF78-E035D3E83368}</productID>
					<productID>{D4E86102-76C1-458C-B0C2-F42B43CAD3CC}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DBAAC357-96E7-459F-B115-B14E29F652EF}</productID>
					<productID>{E2821E0B-CB08-41BD-AE01-A9068F7B8771}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID>
					<productID>{FF56A0C1-3413-4024-89A6-0FB565B2E78C}</productID></dependencies></product>
			<product name="NI TDM Excel Add-In" UC="{6D2EBDAF-6CCD-44F3-B767-4DF9E0F2037B}" productID="{9DFD2D10-299D-4A37-9267-4F28E974F403}" path="(None)" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49155">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID></dependencies></product>
			<product name="NI Variable Engine 2017" UC="{EB7A3C81-1C0F-4495-8CE5-0A427E4E6285}" productID="{3011FA37-DCC4-4BF8-8900-12D68EC7996F}" path="(None)" flavorID="DefaultFull" flavorName="Full" verRestr="false" coreVer="17.0.49152">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{26B72B11-2EF9-4F28-9D4B-9ABD3E854149}</productID>
					<productID>{5691A0DE-3987-4595-A7F8-91133A3C1437}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{5FE7B722-6061-4AFA-A26F-2979CB4FEA40}</productID>
					<productID>{68428815-FD93-4897-BC4A-EC5E3194C4E7}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{78C76251-4DA2-4142-9C57-933B559F6E18}</productID>
					<productID>{9A1C4805-EB50-44F1-87C7-29F5574B44E4}</productID>
					<productID>{DA09F5A1-AA07-467D-A0B5-31D9EC8B5048}</productID>
					<productID>{DDFE3456-19AC-42FC-92C1-CFC10E43A97D}</productID>
					<productID>{F05EC50F-B2B4-4B87-A32C-6F9AD11D1B49}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID></dependencies></product>
			<product name="3D Graph Control Support" UC="{578B3422-EAE6-428C-A17A-7549578FE2C1}" productID="{36E48952-DC01-4739-848E-EA7DC71FB485}" path="(None)" flavorID="Full" flavorName="Full" verRestr="false" coreVer="8.63.49152">
				<dependencies>
					<productID>{0EF046E4-E973-4851-818F-938552DB2E07}</productID>
					<productID>{17349EEB-C92B-4E22-9BC0-C6D5CD6E380C}</productID>
					<productID>{5F956678-03F3-4CF5-88C4-78E8181E2081}</productID>
					<productID>{6EF29D99-5FE4-4D63-87DE-0644222061A2}</productID>
					<productID>{FE7D71A2-BF64-441C-9489-BE6F6937B98E}</productID></dependencies></product>
			<product name="NI-Reports Support" UC="NIReports.02FA89C0_81CC_4586_8ECB_48D58CFAC0B4" productID="2.3.0" path="(None)" flavorID="_full_" flavorName="Full" verRestr="false" coreVer="2.3.0"/></baselineProducts>
		<Projects NumProjects="1">
			<Project000 ProjectID="0" ProjectAbsolutePath="e:\GitWorkplace\Sinoagg\Software\SA6101_realTime\SA6101.prj" ProjectRelativePath="SA6101.prj"/></Projects>
		<buildData progressBarRate="1.318385544528385">
			<progressTimes>
				<Begin>0.000000000000000</Begin>
				<ProductsAdded>0.700990914352544</ProductsAdded>
				<DPConfigured>1.484110214881900</DPConfigured>
				<DPMergeModulesAdded>6.911953850620389</DPMergeModulesAdded>
				<DPClosed>9.403820546957098</DPClosed>
				<DistributionsCopied>9.504620373167006</DistributionsCopied>
				<End>75.850346217025759</End></progressTimes></buildData>
	</msi>
</distribution>
