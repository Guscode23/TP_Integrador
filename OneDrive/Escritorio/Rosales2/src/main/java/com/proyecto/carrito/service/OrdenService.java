package com.proyecto.carrito.service;

import java.util.List;
import java.util.Optional;

import org.springframework.data.jpa.repository.JpaRepository;

import com.proyecto.carrito.model.Cliente;
import com.proyecto.carrito.model.DetalleOrden;
import com.proyecto.carrito.model.Transaccion;

import jakarta.transaction.Transaction;

public interface OrdenService{
	List<Transaccion> findAll();
	Optional<Transaccion> findById(Integer id);
	Transaccion save (Transaccion orden);
	String generarNumeroOrden();
	List<Transaccion> findByUsuario (Cliente usuario);
	
}
