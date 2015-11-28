-- phpMyAdmin SQL Dump
-- version 4.0.10deb1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Nov 28, 2015 at 05:27 PM
-- Server version: 5.5.44-0ubuntu0.14.04.1
-- PHP Version: 5.5.9-1ubuntu4.13

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `proyek_akhir`
--

-- --------------------------------------------------------

--
-- Table structure for table `class_log`
--

CREATE TABLE IF NOT EXISTS `class_log` (
  `no` int(15) NOT NULL AUTO_INCREMENT,
  `card_uid` varchar(8) NOT NULL,
  `timestamp` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`no`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=80 ;

--
-- Dumping data for table `class_log`
--

INSERT INTO `class_log` (`no`, `card_uid`, `timestamp`) VALUES
(51, '86A056C', '2015-11-26 19:48:51'),
(52, '86A056C', '2015-11-26 19:49:04'),
(53, '14EC16B', '2015-11-26 19:49:17'),
(54, '86A056C', '2015-11-26 19:49:32'),
(55, '86A056C', '2015-11-26 19:50:18'),
(56, '86A056C', '2015-11-26 19:51:32'),
(57, '86A056C', '2015-11-26 19:51:52'),
(58, '14EC16B', '2015-11-26 19:52:15'),
(59, '86A056C', '2015-11-26 19:52:35'),
(60, '86A056C', '2015-11-26 19:52:49'),
(70, '14EC16B', '2015-11-26 20:19:00'),
(71, '86A056C', '2015-11-26 20:19:15'),
(72, '586A056', '2015-11-27 02:43:05'),
(73, '586A056', '2015-11-27 02:43:39'),
(74, '586A056', '2015-11-27 02:44:20'),
(75, '514EC16', '2015-11-27 02:45:23'),
(76, '886A056', '2015-11-27 02:46:18'),
(77, '514EC16', '2015-11-27 02:47:37'),
(78, '886A056', '2015-11-27 02:48:18'),
(79, '86A056C', '2015-11-27 03:13:02');

-- --------------------------------------------------------

--
-- Table structure for table `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `id_user` varchar(50) NOT NULL,
  `password` varchar(50) NOT NULL,
  `nama_lengkap` varchar(100) NOT NULL,
  `email` varchar(100) NOT NULL,
  `level` varchar(50) NOT NULL DEFAULT 'user',
  PRIMARY KEY (`id_user`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user`
--

INSERT INTO `user` (`id_user`, `password`, `nama_lengkap`, `email`, `level`) VALUES
('admininstrator', 'b64d11ac02225d0108763ee25e95a105', 'admininstrator', 'admininstrator@admininstrator.admininstrator', 'admin');

-- --------------------------------------------------------

--
-- Table structure for table `user_uid`
--

CREATE TABLE IF NOT EXISTS `user_uid` (
  `no` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(35) NOT NULL,
  `uid` varchar(8) NOT NULL,
  PRIMARY KEY (`no`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=6 ;

--
-- Dumping data for table `user_uid`
--

INSERT INTO `user_uid` (`no`, `name`, `uid`) VALUES
(1, 'Serli S', '86A056C'),
(2, 'Rendro Endoy', '14EC16B'),
(3, 'Serli S', '586A056'),
(4, 'Rendro Ndoy', '514EC16'),
(5, 'Serli S', '886A056');

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
