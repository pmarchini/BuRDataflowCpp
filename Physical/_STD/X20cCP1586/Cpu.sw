﻿<?xml version="1.0" encoding="utf-8"?>
<?AutomationStudio Version=4.7.2.98?>
<SwConfiguration CpuAddress="SL1" xmlns="http://br-automation.co.at/AS/SwConfiguration">
  <TaskClass Name="Cyclic#1" />
  <TaskClass Name="Cyclic#2" />
  <TaskClass Name="Cyclic#3" />
  <TaskClass Name="Cyclic#4">
    <Task Name="Dataflow" Source="_dataflow.Dataflow.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
    <Task Name="DataflowMi" Source="_dataflow.DataflowMirror.prg" Memory="UserROM" Language="ANSIC" Debugging="true" />
  </TaskClass>
</SwConfiguration>